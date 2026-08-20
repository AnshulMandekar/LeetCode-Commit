import urllib.request
import json
import os
import re
import html
from datetime import datetime

# LeetCode GraphQL Endpoint
LEETCODE_GRAPHQL_URL = ""

def fetch_daily_challenge():
    """Queries LeetCode GraphQL API for the Question of the Day."""
    query = """
    query activeDailyCodingChallengeQuestion {
      activeDailyCodingChallengeQuestion {
        date
        link
        question {
          questionFrontendId
          title
          titleSlug
          difficulty
          content
          codeSnippets {
            lang
            langSlug
            code
          }
        }
      }
    }
    """
    req = urllib.request.Request(
        LEETCODE_GRAPHQL_URL,
        data=json.dumps({"query": query}).encode("utf-8"),
        headers={
            "Content-Type": "application/json",
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36"
        },
        method="POST"
    )
    try:
        with urllib.request.urlopen(req) as response:
            res = json.loads(response.read().decode("utf-8"))
            return res.get("data", {}).get("activeDailyCodingChallengeQuestion")
    except Exception as e:
        print(f"Error querying LeetCode GraphQL API: {e}")
        return None

def fetch_cpp_solution(title_slug):
    """Attempts to fetch the C++ solution from kamyu104's LeetCode Solutions repository."""
    url = f"https://raw.githubusercontent.com/kamyu104/LeetCode-Solutions/master/C++/{title_slug}.cpp"
    req = urllib.request.Request(
        url,
        headers={
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36"
        }
    )
    try:
        with urllib.request.urlopen(req) as response:
            if response.status == 200:
                print(f"Successfully retrieved C++ solution for '{title_slug}' from kamyu104.")
                return response.read().decode("utf-8"), True
    except Exception as e:
        print(f"Could not retrieve solution from kamyu104 for '{title_slug}': {e}")
    return "", False

def clean_html_description(html_content):
    """Converts basic HTML description tags to clean Markdown for comment blocks."""
    if not html_content:
        return ""
    
    text = html_content
    # Replace paragraphs and breaks with newlines
    text = re.sub(r'</?p>', '\n', text)
    text = re.sub(r'<br\s*/?>', '\n', text)
    
    # Replace formatting tags
    text = re.sub(r'</?strong>', '**', text)
    text = re.sub(r'</?code>', '`', text)
    text = re.sub(r'</?em>', '*', text)
    
    # Format lists
    text = re.sub(r'</?ul>', '\n', text)
    text = re.sub(r'</?ol>', '\n', text)
    text = re.sub(r'<li>', '- ', text)
    text = re.sub(r'</li>', '\n', text)
    
    # Strip any remaining HTML tags
    text = re.sub(r'<[^>]+>', '', text)
    
    # Unescape HTML entities (e.g., &lt;, &gt;, &quot;, &nbsp;)
    text = html.unescape(text)
    
    # Normalize excessive newlines
    text = re.sub(r'\n\s*\n+', '\n\n', text)
    return text.strip()

def main():
    print("Fetching Daily LeetCode Challenge...")
    daily_info = fetch_daily_challenge()
    if not daily_info:
        print("Failed to fetch daily challenge details. Exiting.")
        return

    # Extract info
    date_str = daily_info["date"]
    link_relative = daily_info["link"]
    question = daily_info["question"]
    
    frontend_id = question["questionFrontendId"]
    title = question["title"]
    title_slug = question["titleSlug"]
    difficulty = question["difficulty"]
    content = question["content"]
    code_snippets = question.get("codeSnippets", [])
    
    # Format links
    problem_url = f"" if link_relative.startswith("/") else link_relative
    
    # Get C++ boilerplate snippet
    cpp_snippet = ""
    for snippet in code_snippets:
        if snippet["langSlug"] == "cpp":
            cpp_snippet = snippet["code"]
            break
            
    # Try fetching the solution
    solution_code, solved = fetch_cpp_solution(title_slug)
    
    # Clean the HTML content description
    clean_desc = clean_html_description(content)
    
    # Format description into C++ comments
    commented_description = ""
    for line in clean_desc.split('\n'):
        safe_line = line.replace("*/", "* /")
        commented_description += f" * {safe_line}\n"

    # Assemble file content
    file_content = f"""// Date: {date_str}
// Problem: {title}
// Difficulty: {difficulty}
// URL: {problem_url}

/*
 * Description:
{commented_description} */

"""
    if solved:
        # Check if the solution already has includes or starts with some boilerplate, 
        # otherwise we append it to our metadata header.
        file_content += solution_code
    else:
        file_content += f"""// NOTE: Solution not automatically found. Feel free to implement it below!

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

{cpp_snippet}
"""

    # Ensure problems directory exists
    os.makedirs("problems", exist_ok=True)
    
    # Save C++ file
    filename = f"{date_str}-{title_slug}.cpp"
    filepath = os.path.join("problems", filename)
    
    with open(filepath, "w", encoding="utf-8") as f:
        f.write(file_content)
    print(f"C++ file written to {filepath}")
    
    # Update README.md progress table
    readme_path = "README.md"
    if os.path.exists(readme_path):
        with open(readme_path, "r", encoding="utf-8") as f:
            readme_content = f.read()
            
        if f"problems/{filename}" in readme_content:
            print(f"Entry for {filename} already exists in README.md. Skipping README update.")
        else:
            difficulty_map = {
                "Easy": "🟢 Easy",
                "Medium": "🟡 Medium",
                "Hard": "🔴 Hard"
            }
            diff_display = difficulty_map.get(difficulty, difficulty)
            status_display = "✅ Solved" if solved else "📝 Template"
            solution_link = f"[Solution](problems/{filename})"
            problem_title_link = f"[{title}]({problem_url})"
            
            row = f"| {date_str} | {frontend_id} | {problem_title_link} | {diff_display} | {status_display} | {solution_link} |\n"
            
            start_tag = "<!-- LEETCODE_LIST_START -->"
            if start_tag in readme_content:
                parts = readme_content.split(start_tag)
                new_readme = parts[0] + start_tag + "\n" + row + parts[1]
                with open(readme_path, "w", encoding="utf-8") as f:
                    f.write(new_readme)
                print("README.md progress table updated.")
            else:
                print("Warning: '<!-- LEETCODE_LIST_START -->' placeholder tag not found in README.md.")
    else:
        print("Warning: README.md not found in the root directory.")

if __name__ == "__main__":
    main()
