# Contributing to webserv

Welcome to the team! To ensure our collaboration is smooth and effective, please follow these guidelines. A consistent workflow helps us build better software, faster.

## The Core Workflow: From Issue to Merge

Our workflow is centered around **GitHub Issues**. Every new feature, bug fix, or chore starts as an issue.

1.  **Create or Claim an Issue:**
    * Before writing any code, create a new issue on GitHub to describe the task. This lets everyone know what's being worked on.
    * If you're starting work on an existing issue, assign it to yourself or leave a comment.

2.  **Create a Branch:**
    * Create a descriptive branch for your task, prefixed with your initials.
    * Always branch from the most recent `main` branch.

    ```bash
    # Make sure your local main is up-to-date
    git checkout main
    git pull origin main

    # Create your new branch
    # Format: <initials>/<issue-number>-<short-description>
    git checkout -b ab/12-implement-request-parser
    ```

3.  **Code & Commit:**
    * Write your code, following the project's [CODING_STYLE.md](CODING_STYLE.md).
    * Commit your changes using the **Conventional Commits** format.

    ```bash
    # Example commit
    git add src/http/request_parser.cpp include/http/request_parser.hpp
    git commit -m "feat(parser): add basic HTTP request line parsing"
    ```

4.  **Open a Pull Request (PR):**
    * Push your branch to GitHub and open a Pull Request to merge into the `main` branch.
    * In the PR description, link the issue it resolves by writing `Closes #12`.
    * Fill out the PR template to describe your changes.

5.  **Review & Merge:**
    * At least one other team member must review the PR.
    * Once the PR is approved, the author can merge it into `main` using **Squash and merge**.
    * Delete the branch after merging.

## Commit Conventions

We use **Conventional Commits**: `<type>(<scope>): <subject>`

* **`feat`**: A new feature.
* **`fix`**: A bug fix.
* **`chore`**: Routine tasks (build process, etc).
* **`docs`**: Documentation changes.
* **`style`**: Formatting changes.
* **`refactor`**: Code changes that neither fix a bug nor add a feature.
* **`test`**: Adding or correcting tests.

## Communication

* **Tasks & Bugs:** Use **GitHub Issues**.
* **Code-Specific Discussion:** Use **Pull Request comments**.
* **Quick Questions & General Chat:** Use **Slack**.

Happy coding! ✨
