# cpp-term-project

SEU term project of a banking system, written with C++ and Qt 6.

Problem 1：Bank Account Management System

Description of the problem：

Please use the object-oriented programming techniques learned in this course, such as inheritance, derivation, polymorphism, file processing, etc., to develop a bank account management system.

The bank account management system includes two types of accounts: users and bank employees.

The user account can be separated into two subtype accounts: current account and savings account. These two accounts under the same user name share basic user information: name, ID card number, mobile phone number, login password, etc. There is no interest in the current account, which can complete the functions of withdrawal (from current account or own savings account), transfer (to other people's or own savings account), deposit (to current account or savings account), query, etc. The interest in the savings account is calculated based on the interest rate set by bank employees. The user who has a savings account must open a current account. When the principal of a savings account changes, the interest shall be calculated automatically according to the interest rate and principal deposit time. The balance of the account shall be updated then. Only the savings account can carry out the amount transfer operation with the current account under the same user name.

The bank employee account should contain the name, ID card number, mobile phone number, employee number, login password and other information. It can open an account (current account or savings account), close an account (current account or savings account), query the account, and the user account can import and export files in batch from the text file.

Users and bank employees log in through a simple text menu interface and perform corresponding operations.

中文：

请综合利用本课程中学习的面向对象编程相关技术，如继承、派生、多态、文件处理、容器等。实现一个银行账户管理系统。

银行账户管理系统中包括用户及银行职员两类人员。

用户账户分为两种类型：活期账户和储蓄账户。两个账户共享基本用户信息：姓名、身份证号、手机号、密码等。活期账户无利息，可以完成取款（活期账户或本人储蓄账户）、转账（他人、本人储蓄账户）、存款、查询账户余额等功能。储蓄账户中本金利息按银行职员设定利率计算。储蓄账户本金变化时应自动根据利率及本金存放时间计算利息，并更新账户余额。开设储蓄账户的用户必须开设活期账户，仅储蓄账户仅可与本人名下的活期账户进行金额互转操作。

银行职员账户需包含姓名、身份证号、手机号、职工号、登录密码等信息，可以进行开户（活期账户或储蓄账户）、销户（活期账户或储蓄账户）、账户查询，用户账户可从文本文件中批量导入及批量导出文件等功能。

用户及银行职员通过简易的文字菜单式系统界面登录后进行相应操作。
