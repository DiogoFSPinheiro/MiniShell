# MiniShell Loggs 🗃️

### 📅 **10/07**

* Done parser with pipes and quotes;
* Done some attribution of data in nodes called tokens;
* Tested if the data is correct in said nodes;
* Didn't free all the memory allocated;
* Got the code generally organized;

✏️ ${{\color{lightgreen}{\textsf{TODO}}}}\$

* Deal with single quotes;
* Deal with redirects;

#

### 📅 **11/07**

* Fix bugg on quotes;
* Done parser on single quotes;
* Polish Skip quotes and single quotes functions;
* Almost done parser with redirect - < << >> >;
* Started working on env (Pedro)

✏️ ${{\color{lightgreen}{\textsf{TODO}}}}\$

* Fix bug on redirect;
* Ajust .h need to clean up and review logic;
* Do a new pliter to place spaces in relevant chars;
* Make a new split func adapted to this project;

#

### 📅 **12/07**

* Fix bugg on quotes;
* Done done parser with redirect - < << >> >;
* Fix bug on redirect;

✏️ ${{\color{lightgreen}{\textsf{TODO}}}}\$

* Ajust .h need to clean up and review logic;
* Make a new split func adapted to this project;
* Do a new pliter to place spaces in relevant chars;
#

### 📅 **15/07**

* Done new pliter to place spaces in relevant chars;
* Bug fixing with new plitter;
* Found bug in "ola"'ola'"ola" -> it doesnt put spaces in bettwin ""
* Cleaned some code

✏️ ${{\color{lightgreen}{\textsf{TODO}}}}\$

* Clean more code
* Ajust .h need to clean up and review logic;
* Make a new split func adapted to this project;

#

### 📅 **16/07**

* Done a new split func adapted to this project;
* Checked leaks, fixed all leaks;
* Ajusted some of the .h;
* Done init Tokens with all data;

✏️ ${{\color{lightgreen}{\textsf{TODO}}}}\$

* Check if component is flag;
* Polish main;

#

### 📅 **17/07**

* Done typeing if component is flag (i only accept 1 flag as i think is enough as the subject tells it);

✏️ ${{\color{lightgreen}{\textsf{TODO}}}}\$


#

### 📅 **31/07**

* Started altering data to expanded form;

✏️ ${{\color{lightgreen}{\textsf{TODO}}}}\$

* Finish the expand part;

#

### 📅 **01/08**

* Got the ~ expanded on the basic part;
* Got the env saved in a struct;
* Made func to retrive the data from env;
* Made env uptade and free itself when needed;

✏️ ${{\color{lightgreen}{\textsf{TODO}}}}\$

* Continue to expand ~;
* Reforce the expand logic;
* Continue to the $ expansions;

#

### 📅 **02/08**

* Done Expand on ~ correctly;
* Done Expand on $ with 0 and 1->9;
* Done Expand on $ with " and not with ';
* Done all of this with no leaks;

✏️ ${{\color{lightgreen}{\textsf{TODO}}}}\$

* Need get a way to expand inside a str "             $USER               ";
* Need to norminete expand.c

#

### 📅 **03/08**

* ReDone Expand on $USER 

✏️ ${{\color{lightgreen}{\textsf{TODO}}}}\$

* Continue expand on $

#