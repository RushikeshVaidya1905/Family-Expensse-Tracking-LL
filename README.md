This will track the Family Expense of each and every member. The Expense Tracking System is an application to efficiently track and manage family expenses. It allows for individual and family-level expense tracking, providing insights into category-wise expenses, individual contributions, and overall spending trends. The system is implemented using arrays of structures for storing and organizing data.

Features

--User Management AddUser():

Add a new user, storing them in a sorted order based on their User ID.

--Family Management CreateFamily():

Create families with 1 to 4 members, calculate total monthly family income and expenses automatically. Update_or_delete_individual_Family_details():

Update individual or family details.

Deleting a single individual with only one member in the family automatically deletes the family.

--Expense Management

AddExpense():

Add expenses for users, categorized by Rent, Utility, Grocery, Stationary, or Leisure, and stored in sorted order by User ID and Expense ID. Update_delete_expense():

Update or delete an existing expense, automatically recalculating all associated totals.

--Expense Tracking and Analysis

Get_total_expense():

Displays the total family expense for the month. Indicates whether the expenses are within or surpass the total income, along with the difference. Get_categorical_expense(string category):

Prints the total expense for a specific category for the family. Shows individual contributions in sorted order by amount. Get_highest_expense_day():

Prints the date with the highest family expense. Get_individual_expense(UserID):

Displays the total expense for a specific user for the month. Provides a breakdown of their category-wise expenses in descending order.
