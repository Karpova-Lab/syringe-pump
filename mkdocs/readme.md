
# Hardware documenation template
This is a template for creating documentation for hardware projects. It is built on top of the following projects:

- [MkDocs](https://github.com/mkdocs/mkdocs) - a static website generator
- [Material for MkDocs](https://github.com/squidfunk/mkdocs-material) - a theme for MkDocs
- [Mike](https://github.com/jimporter/mike) - a tool for publishing and managing multiple documentation versions
- [Mkdocs Markdown includer plugin](https://github.com/mondeja/mkdocs-include-markdown-plugin)


## Setup

Add this repository as a submodule by going to the top level of your project and running the following from the command line:

```
git submodule add https://github.com/alustig3/mkdocs.git mkdocs && git submodule update --init --recursive
```


### Install Python libraries
Python dependencies are managed using [uv](https://github.com/astral-sh/uv?tab=readme-ov-file#getting-started).

You can run the following command to either install uv or update your current installation.

on macOS and Linux:
```
curl -LsSf https://astral.sh/uv/install.sh | sh
```
on Windows
```
powershell -ExecutionPolicy ByPass -c "irm https://astral.sh/uv/install.ps1 | iex"
```


Enter the mkdocs directory and sync the project using uv
```
cd mkdocs/
```
```
uv sync
```

## Serve docs
From within the `mkdocs/` folder run
```
uv run mkdocs serve
```

## Publish docs

### Setup GitHub Pages

- go to `Settings -> Pages`
- Set the Build and deployment source to `Deploy from a branch`
- Set the branch to `gh-pages` and `/(root)`

![pages setup](/pages_setup.png)

### Deploy using Mike

make sure you are in the `mkdocs/` folder
```
cd mkdocs/
```

#### First time setup
```
uv mike delete --all
```

```
uv mike deploy v1.0 latest
```

```
uv mike set-default latest
```

#### Deploying a new version

```
uv mike deploy --update-aliases v1.1 latest
```