#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_SIZE 50
#define FAMILY_SIZE 4
#define CATEGORY_SIZE 15
#define DAY 10
#define MONTH 12
#define NO_CATEGORY 5

typedef enum{FAILURE,SUCCESS} status_code;
typedef struct Family_Tag family;

//Date Structure
typedef struct Date_Tag
{
    int day;
    int month;
}date;

//User Structure
typedef struct User_Tag
{
    int user_id;
    char name[NAME_SIZE];
    float income;
    family* family_id; //Family id where it belongs
    struct User_Tag* next;
}user;

//Family Structure
typedef struct Family_Tag
{
    int family_id;
    char family_name[NAME_SIZE];
    user* members[FAMILY_SIZE]; //Mmbers of the family
    float family_income; //Income of the all family
    float family_expense[MONTH]; //Expense for all months in array
    struct Family_Tag* next;
}family;


//Expense Structure
typedef struct Expense_Tag
{
    int expense_id;
    user* user;
    char category[CATEGORY_SIZE];
    float amount;
    date expense_date;
    struct Expense_Tag* next;
}expense;

//Creates a user and gives output the pointer of that structure
user* CreateUser(int id , char* name , float income)
{
    user* newuser = (user*) malloc (sizeof(user));
    newuser -> user_id = id;
    newuser -> income = income;
    strcpy(newuser -> name , name);
    newuser -> family_id = NULL;
    newuser -> next = NULL;
    return newuser;
}

status_code CreateFamily(family** familyptr , user** user_head);
status_code Update_or_delete_individual_Family_details(user** user_head , family** family_head);

//Finds user by the given user id and returns the pointer of the user structure
user* FindUser(int user_id , user* head)
{
    user* temp = head;
    while(temp != NULL && temp -> user_id != user_id)
    {
        temp = temp -> next;
    }
    return temp;
}

//Finds the family by the given family id and returns the pointer of that family structure
family* FindFamily(int family_id , family* head)
{
    family* temp = head;
    while(temp != NULL && temp -> family_id != family_id)
    {
        temp = temp -> next;
    }
    return temp;
}

//Find the expense by the given expense id and return the pointer of that expense structure
expense* FindExpense(int expense_id , expense* head)
{
    expense* temp = head;
    while(temp != NULL && temp -> expense_id != expense_id)
    {
        temp = temp -> next;
    }
    return temp;
}

//First Function
status_code AddUser(user** headptr , family** familyptr , int in_family)
{
    //Return type
    status_code sc = SUCCESS;
    user* head = (*headptr);
    int id;
    char name[NAME_SIZE];
    float income;
    printf("Enter ID of User\n");
    scanf("%d",&id);
    //Check if already available or not
    if(FindUser(id,head) != NULL)
    {
        printf("User is already Present\n");
        sc = FAILURE;
    }
    else
    {
        //Takes the input from the user
        printf("Enter the name of the user\n");
        scanf("%s",name);
        printf("Enter the income of the user\n");
        scanf("%f",&income);
        //Creating a new user with above information
        user* newuser = CreateUser(id,name,income);
        //Checking where to insert this user now
        user* prev = NULL;
        user* curr = head;
        if(head == NULL)
        {
            (*headptr) = newuser;
        }
        else
        {
            while(curr != NULL && curr -> user_id < id) //Go till you don't find id greater than the user id for insertion sort
            {
                prev = curr;
                curr = curr -> next;
            }
            if(prev == NULL) //Insert at start
            {
                newuser -> next = head;
                (*headptr) = newuser;
            }
            else
            {
                newuser -> next = curr;
                prev -> next = newuser;
            }
        }
        if(in_family == 0) //If the Input is given by the create family function then we don't want to ask this question again
        {
            //Here we have to add this user in family
            int ip;
            printf("To create family give input as 1 else to add user in family give input as 0\n");
            scanf("%d",&ip);
            if(ip == 1)
            {
                CreateFamily(familyptr,headptr);
            }
            else
            {
                //Send this to update family function
                Update_or_delete_individual_Family_details(headptr,familyptr);
            }
        }
    }
        
}

//Creates a pointer to the expense structure and returns the pointer
expense* CreateExpense(int expid , float expense_amt , char* cat , date expdate)
{
    expense* new_exp = (expense*) malloc (sizeof(expense));
    new_exp -> amount = expense_amt;
    new_exp -> expense_id = expid;
    new_exp -> expense_date.day = expdate.day;
    new_exp -> expense_date.month = expdate.month;
    strcpy(new_exp -> category , cat);
    new_exp -> user = NULL;
    new_exp -> next = NULL;
    return new_exp;
}

//Adds expense to the expense list
status_code AddExpense(expense** expense_headptr , user* user_head )
{
    //Return type
    status_code sc = SUCCESS;
    //Takes the inputs of essentials from the user
    int user_id,exp_id;
    float expense_amt;
    date exp_date;
    char exp_cat[CATEGORY_SIZE];
    printf("Enter the user id for the expense\n");
    scanf("%d",&user_id);
    //Finds the user by given user id and gives it to the user of new_exp
    user* userpoint = FindUser(user_id,user_head);
    if(userpoint != NULL)
    {
        printf("Enter the expense id of the expense\n");
        scanf("%d",&exp_id);
        printf("Enter the category of the expense\n");
        scanf("%s",exp_cat);
        printf("Enter the expense amount\n");
        scanf("%f",&expense_amt);
        printf("Enter the day and month of the expense\n");
        scanf("%d%d",&exp_date.day,&exp_date.month);
        //Creates a node
        expense* new_exp = CreateExpense(exp_id,expense_amt,exp_cat,exp_date);
        new_exp -> user = userpoint;
        //create a curr and prev to add this in the list
        expense* curr = (*expense_headptr);
        expense* prev = NULL;
        //Go to the point where the other expenses by that user are present
        while(curr != NULL && curr->user->user_id < user_id)
        {
            prev = curr;
            curr = curr -> next;
        }
        //If both curr and prev will be NULL then the linked list will be empty therefore assign it the value
        if(prev == NULL && curr == NULL)
        {
            (*expense_headptr) = new_exp;
        }
        else
        {
            //Go to the point where we have to add this expense
            while(curr != NULL && curr -> expense_id < exp_id)
            {
                prev = curr;
                curr = curr -> next;
            }
            if(prev == NULL)
            {
                new_exp -> next = curr;
                (*expense_headptr) = new_exp;
            }
            else
            {
                new_exp -> next = curr;
                prev -> next = new_exp;
            }
        }
        family* familypoint = userpoint -> family_id;
        familypoint -> family_expense[exp_date.month-1] = familypoint -> family_expense[exp_date.month-1] + expense_amt;
    }
    else
    {
        printf("User does not exist\n");
        sc = FAILURE;
    }
    return sc;
}

status_code CreateFamily(family** familyptr , user** user_head)
{
    //Return type
    status_code sc = SUCCESS;
    int flag = 0;
    int i=0;
    //Takes the input from the user
    int family_id;
    char family_name[NAME_SIZE];
    user* members[FAMILY_SIZE];
    float income = 0;
    float expense = 0;
    printf("Enter the family id\n");
    scanf("%d",&family_id);
    family* temp = FindFamily(family_id,(*familyptr));
    if(temp != NULL)
    {
        printf("Family Already Exists\n");
        sc = FAILURE;
    }
    else
    {
        printf("Enter the name of family\n");
        scanf("%s",family_name);
        //Create a famly structure pointer and assign those values
        family* new_family = (family*) malloc (sizeof(family));
        new_family -> family_id = family_id;
        strcpy(new_family -> family_name , family_name);
        //Go untill the size of the family
        for(i=0 ; i < FAMILY_SIZE && (!flag); i++)
        {
            user* member;
            int uid;
            printf("Enter the User id of %dth member if no more members then enter -1\n",i+1);
            scanf("%d",&uid);
            if(uid == -1)
            {
                new_family ->members[i] = NULL;
                flag = 1;
            }
            else
            {
                //If the user is not available then add it to the user list
                if(FindUser(uid , (*user_head)) == NULL)
                {
                    printf("Add this user first to the list\n");
                    AddUser(user_head,familyptr,1);
                }
                //Create a user pointer named member and assign it the pointer of that user id
                member = FindUser(uid , (*user_head));
                member -> family_id = new_family;
                new_family -> members[i] = member;
                income = income + member -> income;
                //Expense initialisation
                for(int j=0; j<MONTH ; j++)
                {
                    new_family -> family_expense[j] = 0;
                }
            }
        }
        //Mmber initialisation
        while(flag == 1 && i<FAMILY_SIZE)
        {
            new_family -> members[i] = NULL;
            i++;
        }
        family* prev = NULL;
        family* curr = (*familyptr);
        while(curr != NULL && curr -> family_id < family_id)
        {
            prev = curr;
            curr = curr -> next;
        }
        //Empty family
        if(curr == NULL && prev == NULL)
        {
            (*familyptr) = new_family;
        }
        else
        {
            if(prev == NULL)
            {
                new_family -> next = (*familyptr);
                (*familyptr) = new_family;
            }
            else
            {
                new_family -> next = curr;
                prev -> next = new_family;
            }
        }
    }
    return sc;
}

//Update_or_delete_individual_Family_details
status_code Update_or_delete_individual_Family_details(user** user_head , family** family_head)
{
    status_code sc = SUCCESS;
    int iorf;
    int uord;
    printf("Do you want to do operation on individual(1) or family(0)\n");
    scanf("%d",&iorf);
    if(iorf)
    {
        printf("Do you want to update(0) or delete(1)\n");
        scanf("%d",&uord);
        if(uord)
        {
            int id;
            printf("Enter the user id\n");
            scanf("%d",&id);
            if(FindUser(id,(*user_head)) == NULL)
            {
                printf("No such user\n");
                sc = FAILURE;
            }
            else
            {
                user* curr = (*user_head);
                user* prev = NULL;
                user* user_id = FindUser(id,(*user_head));
                family* family_id = user_id -> family_id;
                int count = 0;
                int position = 0;
                while(family_id->members[count] != NULL)
                {
                    if(family_id->members[count] == user_id)
                    {
                        position = count;
                    }
                    count++;
                }
                while(curr != user_id)
                {
                    prev = curr;
                    curr = curr -> next;
                }
                if(prev == NULL)
                {
                    (*user_head) = (*user_head) -> next;
                }
                else
                {
                    prev -> next = curr -> next;
                }
                family_id -> family_income -= user_id -> income;
                for(int i=position+1; i<FAMILY_SIZE ; i++)
                {
                    family_id -> members[i-1] = family_id -> members[i];
                }
                family_id -> members[FAMILY_SIZE-1] = NULL;
                free(user_id);
                if(count == 1)
                {
                    family* currf = (*family_head);
                    family* prevf = NULL;
                    while(currf != family_id)
                    {
                        prevf = currf;
                        currf = currf -> next;
                    }
                    if(prevf == NULL)
                    {
                        (*family_head) = (*family_head) -> next;
                    }
                    else
                    {
                        prevf -> next = currf -> next;
                    }
                    free(family_id);
                }
            }
        }
        else
        {
            int id;
            printf("Enter the user id\n");
            scanf("%d",&id);
            if(FindUser(id,(*user_head)) == NULL)
            {
                printf("No such user\n");
                sc = FAILURE;
            }
            else
            {
                user* user_id = FindUser(id,(*user_head));
                family* family_id = user_id -> family_id;
                char uname[NAME_SIZE];
                float uincome;
                printf("Enter the name of the user\n");
                scanf("%s",uname);
                printf("Enter the income of the user\n");
                scanf("%f",&uincome);
                family_id -> family_income -= user_id -> income;
                user_id -> income = uincome;
                family_id -> family_income += uincome;
                strcpy(user_id -> name , uname);
            }
        }
    }
    else
    {
        printf("Do you want to update(0) or delete(1)\n");
        scanf("%d",&uord);
        if(uord)
        {
            int fid;
            printf("Enter the family id\n");
            scanf("%d", &fid);

            // Find the family
            family* family_id = FindFamily(fid, (*family_head));
            if (family_id == NULL)
            {
                printf("There does not exist a family with this ID\n");
                sc = FAILURE;
            }
            else
            {
                // Find and remove the family from the linked list
                family* currf = (*family_head);
                family* prevf = NULL;

                while (currf != NULL && currf != family_id)
                {
                    prevf = currf;
                    currf = currf -> next;
                }

                if (prevf == NULL) 
                {
                    // Deleting the first family in the list
                    (*family_head) = currf -> next;
                } 
                else 
                {
                    prevf -> next = currf -> next;
                }

                // Now delete all users in this family
                for (int i = 0; i < FAMILY_SIZE; i++)
                {
                    if (family_id -> members[i] != NULL)
                    {
                        user* temp = family_id -> members[i];

                        // Find and remove the user from the user linked list
                        user* curr = (*user_head);
                        user* prev = NULL;

                        while (curr != NULL && curr != temp)
                        {
                            prev = curr;
                            curr = curr->next;
                        }

                        if (curr != NULL) 
                        {
                            if (prev == NULL) 
                            {
                                // Deleting the first user
                                (*user_head) = curr->next;
                            } 
                            else 
                            {
                                prev->next = curr->next;
                            }

                            free(curr); // Free user memory
                        }
                    }
                }
                // Free the family memory
                free(family_id);
                printf("Family and its members deleted successfully.\n");
            }
        }
        else
        {
            int fid;
            printf("Enter the family id\n");
            scanf("%d",&fid);
            family* family_id = FindFamily(fid,(*family_head));
            if(family_id == NULL)
            {
                printf("There do not exist a family with this id\n");
                sc = FAILURE;
            } 
            else
            {
                int i=0;
                while(family_id -> members[i] != NULL)
                {
                    i++;
                }
                if(i == FAMILY_SIZE)
                {
                    sc = FAILURE;
                    printf("No more family members space is available in this family\n");
                }
                else
                {
                    int uid;
                    printf("Enter the id for new individual\n");
                    scanf("%d",&uid);
                    user* NewUser = FindUser(uid,(*user_head));
                    if(NewUser == NULL)
                    {
                        printf("Add this user first\n");
                        AddUser(user_head,family_head,1);
                    }
                    NewUser = FindUser(uid,(*user_head));
                    NewUser -> family_id = family_id;
                    family_id -> members[i] = NewUser;
                    family_id -> family_income += NewUser-> income;
                }
            }
        }
    }
    return sc;
}

status_code Update_delete_expense(expense** expenseptr , user* user_head)
{
    //Return type
    status_code sc = SUCCESS;
    int op;
    printf("If you want to update an expense enter 1 else to delete enter 0\n");
    scanf("%d",&op);
    int exp_id;
    printf("Enter the Expense id\n");
    scanf("%d",&exp_id);
    //Checks if the expense is present or not
    if(FindExpense(exp_id , (*expenseptr)) == NULL)
    {
        printf("No expense with expense id %d\n",exp_id);
        sc = FAILURE;
    }
    else
    {
        if(op == 1)
        {
            //Take the updated amount of expense
            float newAmt;
            printf("Enter the new amount\n");
            scanf("%f",&newAmt);
            expense* temp = FindExpense(exp_id , (*expenseptr));
            float prevamt = temp -> amount;
            temp -> amount = newAmt;
            user* exp_user = temp -> user;
            family* exp_family = exp_user -> family_id;
            //Add this new expense to the month of the given expense id
            exp_family -> family_expense[temp -> expense_date.month -1] -= prevamt;
            exp_family -> family_expense[temp -> expense_date.month -1] += newAmt;
            
        }
        else
        {
            //Keep previous and curr pointers to check for the expense
            expense* prev = NULL;
            expense* curr = (*expenseptr);
            expense* temp = FindExpense(exp_id , (*expenseptr));
            while(curr != temp)
            {
                prev = curr;
                curr = curr -> next;
            }
            expense* todelete;
            //Delete at start
            if(prev == NULL)
            {
                todelete = (*expenseptr);
                (*expenseptr) = (*expenseptr) -> next;
            }
            else
            {
                todelete = curr;
                prev -> next = curr -> next;
            }
            float amt = temp -> amount;
            user* exp_user = todelete -> user;
            family* exp_family = exp_user -> family_id;
            exp_family -> family_expense[temp -> expense_date.month -1] -= amt;
            free(todelete);
            todelete = NULL;
        }
    }
    return sc;
}

status_code Get_total_expense(expense* expense_head , family* family_head)
{
    //Return type
    status_code sc = SUCCESS;
    int family_id;
    printf("Enter the family id\n");
    scanf("%d",&family_id);
    family* familypoint = FindFamily(family_id,family_head);
    if(familypoint == NULL)
    {
        printf("No such family with id %d is present\n",family_id);
        sc = FAILURE;
    }
    else
    {
        int month,i=0;
        printf("Enter the month for which do we have to calculate\n");
        scanf("%d",&month);
        float total_expense = 0;
        //The below is one of the way by which we can do it
        /*while(familypoint -> members[i] != NULL && i < FAMILY_SIZE) //If the user is not present then there is null there in the structure 
        {
            //Assign the user id of family's ith member
            int user_id = familypoint -> members[i] -> user_id;
            expense* temp = expense_head;
            //Goes to the all expenses in the list
            while(temp != NULL && temp -> user -> user_id < user_id)
            {
                temp = temp -> next;
            }
            //Going till we find the expense done in that month
            while(temp -> user -> user_id == user_id)
            {
                if(temp -> expense_date.month == month)
                {
                    total_expense = total_expense + temp -> amount;
                }
                temp = temp -> next;
            }
            i++;
        }*/
        //Prints the total expense
        total_expense = familypoint->family_expense[month-1];
        printf("The total expense for the month %d is %f\n",month,total_expense);
        //checks for the monthly family income
        if(total_expense > familypoint -> family_income)
        {
            printf("The expense surpasses the income by %f\n",total_expense- (familypoint -> family_income));
        }
        else
        {
            printf("The expense is within the family income and diff is %f\n",(familypoint -> family_income) - total_expense);
        }
    }
    return sc;
}

status_code Get_categorical_expense(expense* expense_head, family* family_head)
{
    // Return type
    status_code sc = SUCCESS;
    int family_id;
    char category[CATEGORY_SIZE];
    printf("Enter the family id\n");
    scanf("%d", &family_id);

    // Assign the family pointer to the familypoint here
    family* familypoint = FindFamily(family_id, family_head);

    // If family is not found
    if (familypoint == NULL)
    {
        printf("There is no family with family id %d\n", family_id);
        sc = FAILURE;
    }
    else
    {
        printf("Enter the category\n");
        scanf("%s", category);
        if(strcmp("Rent", category) == 0 || strcmp("Utility", category) == 0 || strcmp("Grocery", category) == 0 ||strcmp("Stationary", category) == 0 || strcmp("Leisure", category) == 0)
        {
            int i = 0;
            // For sorting we need to store user expenses and their indices
            float ans[FAMILY_SIZE][3];  // Use 3 columns: [expense, user_index, user_id]
            
            // Go through each member of the family
            while (familypoint->members[i] != NULL && i < FAMILY_SIZE)
            {
                float user_exp = 0;
                int user_id = familypoint -> members[i] -> user_id;
                expense* temp = expense_head;
                
                // Go to the expense of the current user
                while (temp != NULL && temp->user->user_id != user_id)
                {
                    temp = temp->next;
                }

                // Sum up expenses in the given category for this user
                while (temp != NULL && temp->user->user_id == user_id)
                {
                    if (strcmp(temp->category, category) == 0)
                    {
                        user_exp += temp->amount;
                    }
                    temp = temp->next;
                }
                
                // Store the user's expense and their index in the family
                ans[i][0] = user_exp;
                ans[i][1] = (float)i;  // Store the index of the user in the family
                ans[i][2] = (float)user_id; // Store the user id for later use in the print statement
                i++;
            }
            
            // Sort the expenses in descending order based on the user expense
            for (int j = 0; j < i - 1; j++)
            {
                for (int k = 0; k < i - j - 1; k++)
                {
                    if (ans[k][0] < ans[k + 1][0])
                    {
                        // Swap the expenses and user indices
                        float temp_exp = ans[k][0];
                        ans[k][0] = ans[k + 1][0];
                        ans[k + 1][0] = temp_exp;
                        
                        float temp_idx = ans[k][1];
                        ans[k][1] = ans[k + 1][1];
                        ans[k + 1][1] = temp_idx;

                        float temp_user_id = ans[k][2];
                        ans[k][2] = ans[k + 1][2];
                        ans[k + 1][2] = temp_user_id;
                    }
                }
            }

            // Calculate the total expense for the category
            float total_expense = 0;
            printf("The expense in the category %s is as follows:\n", category);

            // Print the expenses of all users in sorted order
            for (int o = i - 1; o >= 0; o--)
            {
                printf("User ID - %d with expense of %.2f\n", (int)ans[o][2], ans[o][0]);
                total_expense += ans[o][0];
            }
            
            printf("The total expense by the family is %.2f\n", total_expense);
        }
        else
        {
            printf("Invalid Category\n");
            sc = FAILURE;
        }
    }
    return sc;
}

status_code Get_highest_expense_day(expense* expense_head , family* family_head)
{
    status_code sc = SUCCESS;
    int family_id;
    printf("Enter the family id\n");
    scanf("%d", &family_id);
    
    family* familypoint = FindFamily(family_id, family_head);
    if(familypoint == NULL)
    {
        printf("There is no family with this ID.\n");
        sc = FAILURE;
    }
    else
    {
        //Date structure to store the max expense day
        date max = {-1, -1};  //Initialize max date
        float max_amount = -1;

        // Iterate over months (1 to 12)
        for(int i = 1; i <= MONTH; i++)
        {
            // Iterate over days (1 to 10, as per DAY constant)
            for(int j = 1; j <= DAY; j++)
            {
                float amount = 0;
                // Iterate over family members
                for(int k = 0; k < FAMILY_SIZE; k++)
                {
                    if(familypoint->members[k] != NULL)   
                    {
                        expense* temp = expense_head;
                        // Go through all expenses for the user
                        while(temp != NULL)
                        {
                            if(temp->user->user_id == familypoint->members[k]->user_id && temp->expense_date.day == j && temp->expense_date.month == i)
                            {
                                amount += temp->amount;
                            }
                            temp = temp->next;
                        }
                    }
                }
                // Check if this date has the highest expense
                if(amount > max_amount)
                {
                    max_amount = amount;
                    max.day = j;
                    max.month = i;
                }
            }
        }

        // If no expenses were found, return failure
        if(max_amount == -1)
        {
            printf("No expenses recorded for this family.\n");
            sc = FAILURE;
        }
        printf("The maximum expense day of the family was on day %d, month %d, worth %f rupees.\n",max.day, max.month, max_amount);
    }
    return sc;
}

status_code Get_individual_expense(expense* expense_head , user* user_head)
{
    //Return type
    status_code sc = SUCCESS;
    int user_id;
    printf("Enter the user id\n");
    scanf("%d",&user_id);
    user* userpoint = FindUser(user_id,user_head);
    if(userpoint == NULL)
    {
        printf("No such user exists with %d user id\n",user_id);
        sc = FAILURE;
    }
    else
    {
        int month;
        printf("Enter the month for which the expense is to given\n");
        scanf("%d",&month);
        //Structure for the category wise expense
        typedef struct Individual_Tag
        {
            float amount;
            char category[CATEGORY_SIZE];
        }Individual;
        expense* temp = expense_head;
        //Moving till the user id
        while(temp != NULL && temp -> user -> user_id < user_id)
        {
            temp = temp -> next;
        }
        if(temp == NULL)
        {
            printf("No expense by the user");
        }
        else
        {
            //Creating array of the structures of the number of categories
            Individual indi_user[NO_CATEGORY];
            //Initialising it
            for(int i=0 ; i<NO_CATEGORY ; i++)
            {
                indi_user[i].amount = 0;
            }
            strcpy(indi_user[0].category,"Rent");
            strcpy(indi_user[1].category,"Utility");
            strcpy(indi_user[2].category,"Grocery");
            strcpy(indi_user[3].category,"Stationary");
            strcpy(indi_user[4].category,"Leisure");
            //Pass through each and every expense by that user
            while(temp != NULL && temp -> user -> user_id == user_id)
            {
                //If the expense is for the given month then add it
                if(temp -> expense_date.month == month)
                {
                    for(int i=0 ; i < NO_CATEGORY ; i++)
                    {
                        if(strcmp(temp -> category , indi_user[i].category) == 0)
                        {
                            indi_user[i].amount += temp->amount;
                        }
                    }
                }
                temp = temp->next;
            }
            //Sorting this category wise expense for the given month
            for(int j=0 ; j < NO_CATEGORY-1; j++)
            {
                for(int k=0 ; k<NO_CATEGORY-j-1 ; k++)
                {
                    if(indi_user[k].amount > indi_user[k+1].amount)
                    {
                        float temp = indi_user[k].amount;
                        indi_user[k].amount = indi_user[k+1].amount;
                        indi_user[k+1].amount = temp;
                        char name[CATEGORY_SIZE];
                        strcpy(name,indi_user[k].category);
                        strcpy(indi_user[k].category,indi_user[k+1].category);
                        strcpy(indi_user[k+1].category,name);
                    }
                }
            }
            float total_expense = 0;
            printf("The individual expenses as below\n");
            for(int i=NO_CATEGORY-1 ; i>=0 ; i--)
            {
                total_expense += indi_user[i].amount;
                printf("%f is the expense for %s\n",indi_user[i].amount,indi_user[i].category);
            }
            printf("The total expense by the user %d for the month %d is %f\n",user_id,month,total_expense);
        }
    }
    return sc;
}

void Input_Family(user** User_head , family** family_head , expense** expense_head)
{
    //Openes Family file
    FILE* file2 = fopen("families.csv","r");
    char line2[256];
    if(file2 == NULL)
    {
        printf("Unable to open family file\n");
    }
    else
    {
        //Go untill the family file become empty
        while(fgets(line2, sizeof(line2), file2))
        {
            int family_id;
            char fname[NAME_SIZE];
            //Takes the input
            if(sscanf(line2, "%d,%s",&family_id,fname) == 2)
            {
                family* new_family = (family*)malloc(sizeof(family));
                //Assign the input and initialise other values as well
                new_family ->family_id = family_id;
                strcpy(new_family -> family_name,fname);
                for(int i=0 ; i<FAMILY_SIZE; i++)
                {
                    new_family ->members[i] = NULL;
                }
                //Put this family in the linked list
                family* curr = (*family_head);
                family* prev = NULL;
                //Empty linked list
                if(curr == NULL && prev == NULL)
                {
                    (*family_head) = new_family;
                }
                else
                {
                    while(curr != NULL && curr -> family_id < family_id)
                    {
                        prev = curr;
                        curr = curr -> next;
                    }
                    //Insert at start
                    if(prev == NULL)
                    {
                        new_family -> next = (*family_head);
                        (*family_head) = new_family;
                    }
                    else
                    {
                        new_family -> next = curr;
                        prev -> next = new_family;
                    }
                }
            }
        }
        fclose(file2);
    }
}

void Input_User(user** User_head , family** family_head , expense** expense_head)
{
    //Opens file
    FILE* file1 = fopen("users.csv","r");
    if (file1 == NULL) {
        printf("Unable to open users file\n");
    }
    else
    {
        char line1[256];
        while (fgets(line1, sizeof(line1), file1))
        {
            int uid, fid;
            char name[NAME_SIZE];
            float income;

            if (sscanf(line1, "%d,%49[^,],%f,%d", &uid, name, &income , &fid) == 4)
            {
                // Create a new user
                user* new_user = CreateUser(uid, name, income);

                // Find the family
                family* ufamily = FindFamily(fid, (*family_head));
                if (ufamily == NULL) 
                {
                    printf("Family with ID %d not found. User %s will not be assigned to a family.\n", fid, name);
                } 
                else 
                {
                    new_user->family_id = ufamily;

                    // Add user to family members
                    int i = 0;
                    while (i < FAMILY_SIZE && ufamily->members[i] != NULL) {
                        i++;
                    }

                    if (i < FAMILY_SIZE) 
                    {
                        ufamily->members[i] = new_user;
                        ufamily->family_income += new_user->income;
                    } 
                    else 
                    {
                        printf("Family %d is full, user %s cannot be added.\n", fid, name);
                    }
                }

                // Insert the new user into the sorted linked list
                user* curr = (*User_head);
                user* prev = NULL;

                while (curr != NULL && curr->user_id < uid) {
                    prev = curr;
                    curr = curr->next;
                }

                if (prev == NULL) {
                    new_user->next = (*User_head);
                    (*User_head) = new_user;
                } else {
                    new_user->next = curr;
                    prev->next = new_user;
                }
            }
        }
        fclose(file1);
    }
}

void Input_Expense(user** User_head , family** family_head , expense** expense_head)
{
    FILE* file3 = fopen("expenses.csv", "r");
    if (file3 == NULL) 
    {
        printf("Unable to open expenses file\n");
    }
    else
    {
        char line3[256];
        //Go until the file ends
        while (fgets(line3, sizeof(line3), file3))
        {
            int exp_id, uid, day, month;
            char cat[CATEGORY_SIZE];
            float amt;

            if (sscanf(line3, "%d,%d,%14[^,],%f,%d,%d", &exp_id, &uid, cat, &amt, &month, &day) == 6)
            {
                //Takes input and assigns it
                date edate;
                edate.day = day;
                edate.month = month;

                // Find user associated with the expense
                user* uexp = FindUser(uid, (*User_head));
                if (uexp == NULL) {
                    printf("Warning: User ID %d not found. Expense ID %d not added.\n", uid, exp_id);
                    continue;
                }

                // Create new expense
                expense* new_exp = CreateExpense(exp_id, amt, cat, edate);
                new_exp->user = uexp;

                // Find the family of the user and add expense to the family's monthly expense
                family* fexp = uexp -> family_id;
                
                fexp -> family_expense[month - 1] += amt;
                

                // Insert the new expense into the sorted linked list
                expense* curr = (*expense_head);
                expense* prev = NULL;

                while (curr != NULL && curr->user->user_id < uid) {
                    prev = curr;
                    curr = curr->next;
                }

                while (curr != NULL && curr->user->user_id == uid && curr->expense_id < exp_id) {
                    prev = curr;
                    curr = curr->next;
                }

                if (prev == NULL) {
                    new_exp->next = (*expense_head);
                    (*expense_head) = new_exp;
                } else {
                    new_exp->next = curr;
                    prev->next = new_exp;
                }
            }
        }
        fclose(file3);
    }
}

int main()
{
    user* user_head = NULL;
    family* family_head = NULL;
    expense* expense_head = NULL;
    Input_Family(&user_head,&family_head,&expense_head);
    Input_User(&user_head,&family_head,&expense_head);
    Input_Expense(&user_head,&family_head,&expense_head);
    
    int menu_code,exitloop = 1;
    while(exitloop)
    {
        printf("\tExpense Tracking System\n");
        printf("Menu\n1.Add User\n2.Add Expense\n3.Create Family\n4.Update or delete individual family details\n5.Update or delete expense\n6.Get Total expense\n7.Get categorical expense\n8.Get highest expense day\n9.Get individual expense\n10.Exit\n");
        printf("Enter number between 1 to 10\n");
        scanf("%d",&menu_code);
        if(menu_code < 1 && menu_code > 10)
        {
            printf("Invalid input");
        }
        else
        {
            switch (menu_code)
            {
            case 1:
            {
                status_code sc;
                sc = AddUser(&user_head,&family_head,0);
                if(sc == FAILURE)
                {
                    printf("Operation unsuccessful\n");
                }
                else
                {
                    printf("Operation successful\n");
                }
                break;
            }
            
            case 2:
            {
                status_code sc;
                sc = AddExpense(&expense_head,user_head);
                if(sc == FAILURE)
                {
                    printf("Operation unsuccessful\n");
                }
                else
                {
                    printf("Operation successful\n");
                }
                break;
            }

            case 3:
            {
                status_code sc;
                sc = CreateFamily(&family_head,&user_head);
                if(sc == FAILURE)
                {
                    printf("Operation unsuccessful\n");
                }
                else
                {
                    printf("Operation successful\n");
                }
                break;
            }

            case 4:
            {
                status_code sc;
                sc = Update_or_delete_individual_Family_details(&user_head,&family_head);
                if(sc == FAILURE)
                {
                    printf("Operation unsuccessful\n");
                }
                else
                {
                    printf("Operation successful\n");
                }
                break;
            }

            case 5:
            {
                status_code sc;
                sc = Update_delete_expense(&expense_head,user_head);
                if(sc == FAILURE)
                {
                    printf("Operation unsuccessful\n");
                }
                else
                {
                    printf("Operation successful\n");
                }
                break;
            }

            case 6:
            {
                status_code sc;
                sc = Get_total_expense(expense_head,family_head);
                if(sc == FAILURE)
                {
                    printf("Operation unsuccessful\n");
                }
                else
                {
                    printf("Operation successful\n");
                }
                break;
            }

            case 7:
            {
                status_code sc;
                sc = Get_categorical_expense(expense_head,family_head);
                if(sc == FAILURE)
                {
                    printf("Operation unsuccessful\n");
                }
                else
                {
                    printf("Operation successful\n");
                }
                break;
            }

            case 8:
            {
                status_code sc;
                sc = Get_highest_expense_day(expense_head,family_head);
                if(sc == FAILURE)
                {
                    printf("Operation unsuccessful\n");
                }
                else
                {
                    printf("Operation successful\n");
                }
                break;
            }

            case 9:
            {
                status_code sc;
                sc = Get_individual_expense(expense_head,user_head);
                if(sc == FAILURE)
                {
                    printf("Operation unsuccessful\n");
                }
                else
                {
                    printf("Operation successful\n");
                }
                break;
            }
            
            case 10:
                exitloop = 0;
                break;
            default:
                break;
            }
        }
    }
    return 0;
    
}