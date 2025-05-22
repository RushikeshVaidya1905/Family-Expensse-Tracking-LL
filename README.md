Family Expense Tracking System
This system tracks the family expenses of each and every member in a household. The Expense Tracking System is a console-based application developed to efficiently manage and analyze expenses at both the individual and family levels. It provides detailed insights into category-wise spending, individual contributions, and overall family financial trends.

The entire system is implemented using linked lists to dynamically manage data such as users, families, and expenses. All database-like functionalities — storage, insertion, deletion, and retrieval — are handled through various linked list operations, offering flexible and efficient memory usage.

Features

🧑‍💼 User Management

AddUser()

Add a new user and insert them into the list in sorted order by User ID.

👨‍👩‍👧‍👦 Family Management

CreateFamily()

Create a family with 1 to 4 members. Automatically calculates the total monthly income and expenses of the family.

Update_or_delete_individual_Family_details()
Update details of individuals or entire families.
Deleting the last member of a family automatically removes the family node from the list.

💰 Expense Management

AddExpense()

Add an expense for a user, categorized under:
Rent, Utility, Grocery, Stationary, or Leisure.
Expenses are stored in sorted order by User ID and Expense ID.

Update_delete_expense()
Modify or remove an existing expense.
All related totals are automatically recalculated.

📊 Expense Tracking and Analysis

Get_total_expense()
Displays the total family expense for the month.
Indicates whether the expenses are within or beyond the income, and shows the difference.

Get_categorical_expense(string category)
Displays the total amount spent in a given category for the family.
Lists individual contributions in descending order by amount.

Get_highest_expense_day()
Shows the date with the highest overall family expense.

Get_individual_expense(UserID)
Displays a user’s total expenses for the month.
Breaks down their expenses category-wise, in descending order.

