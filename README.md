# Assessments Framework

## Team

- one
- two

## Features

1. Dual-mode - will accept command line arguments, if none, will offer a GUI
1. Two-Boost libraries included - json and tokenizer 
1. Installer

# Dev notes

Clone solution into VS2019

## To add boost libraries into the project (current version is 1.78.0)
<https://medium.com/@biswa8998/building-c-boost-and-using-bcp-exe-f89881b2cc60>

	change into boost directory and run bootstrap
	change into tools/bcp and run ..\..\b2
	change back up to the top of the boost directory
	bin.v2\tools\bcp\msvc-14.2\release\link-static\threading-multi\bcp.exe
	bin.v2\tools\bcp\msvc-14.2\release\link-static\threading-multi\bcp.exe debug tokenizer json ..\assessments

## To enable installer
<https://stackoverflow.com/a/54889614>


1. Enter Visual Studio .NET 2019 as administrator
1. Click on "Extensions" -> Manage Extensions -> Online
1. Type "Installer Project" on the search box
1. Click on "Install" in Microsoft Visual Studio Installer Project - pay attention to the prompts
1. Restart Visual Studio .NET and follow the instructions to install the extension
1. Rebuild install project
