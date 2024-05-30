[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-718a45dd9cf7e7f842a935f5ebbe5719a5e09af4491e668f4dbf3b35d5cca122.svg)](https://classroom.github.com/online_ide?assignment_repo_id=11531085&assignment_repo_type=AssignmentRepo)
# UCR Housing Website
 
 > Authors: [Sarah Armstrong](https://github.com/saraharmstrong314), [Ashley Han](https://github.com/ahan036), [Javier Herrera](https://github.com/jherr116), [Benjamin Lim](https://github.com/BenBeast229)

## Project Description
### Importance
In our early years at UCR, deciding housing plans was stressful. We didn't know all the available options, which housing options go the fastest, and the pitfalls of UCR's outdated housing website. For example, prices aren't accurate, like saying Glen Mor includes a dining plan when it does not. It would have been useful to have an intuitive interface to explore and compare UCR's housing with accurate information. That's why we've decided to make a new housing website for UCR as our project.
### Tech Stack
* Design: Figma, Lucidchart
* Frontend: HTML, CSS
* Backend: MySQL, JavaScript
* Code editor: VSCode
### Input/Output
A user will be able to select a type of housing, like a dorm or an apartment. For each type of housing, the user can filter the options by different features like price and number of roommates. This will output a filtered display of housing options.
### Features / Epics
* As a user, I can filter housing options so that I can narrow down the options based on features like building, price, and number of roommates. I want to see the displayed options update to reflect my preferences. I want to be able to select one, multiple, or no features  to filter.
* As a user, I can visit any page of the website so that I can select different housing types to compare. I can visit previous pages so that I can compare different housing options when my preferences change, or when I want to compare options of a different housing type.
* As a user, I can read reviews for different housing options so that I can get more insight into housing quality. As a user I can write a review to share my housing experience so that other users get insight into housing I had. As a user I can rate housing options so that I can summarize my experience in a brief, intuitive way.

## User Interface Specification
### Navigation Diagram
![Navigation Diagram](https://cdn.discordapp.com/attachments/1135814914926182581/1143645757832953866/image.png)

### Screen Layouts
![figma](https://github.com/cs100/final-project-noobs/assets/141061656/0bbce05f-9d71-43eb-90bf-3aee2c4c94b0)


## Class Diagram (Before SOLID Principles)
![Class Diagram](https://cdn.discordapp.com/attachments/1036740427170197515/1143648821134512200/image.png)
 
 ## Screenshots
 ![Picture](https://cdn.discordapp.com/attachments/1036740427170197515/1147239123971743855/picture.png)
 ![Picture2](https://cdn.discordapp.com/attachments/1036740427170197515/1147240054150922240/picture2.png)
 ## Installation/Usage
 The website is hosted locally, so it should run as long as 127.0.0.1 refers to the local machine. If for some reason your local machine's IP address is different, then the host name in the database connection credentials needs to be changed to match. VSCode's Live Server extension needs to be installed. Right click index.html and choose the option open with Live Server, which should appear at the top. The website can then be navigated by clicking on buttons, pictures, and the home button in the top left corner. The buttons take you to the filters, and the pictures go to the review pages.
 ## Testing
 Our project was largely tested through the VSCode extension Live Server that allows changes to be viewed continuously. This helped frontend design and identified bugs when working on connecting to the backend. Using the developer tools, we could see what parts of the code caused bugs, and later it would be used to test how the website looks on different screen sizes. Database queries were tested by hosting the website locally and checking outside of VSCode the contents of the table in the database.