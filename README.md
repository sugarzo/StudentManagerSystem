# 123
**c++大作业（大一上）**
**2021年3月至2021年6月**
**在校期间的课设作业，留档**

直接启动exe文件即可（管理员账号密码默认为admin）

（以下为当时交上去的报告书节选）

课 程 设 计 任 务 书 
一、目的任务
目的：   
(1) 掌握面向对象程序设计的思想，能够使用面向对象程序设计思想解决实际问题； 

(2) 完成程序设计和编码，能够灵活运用各种调试命令修改源程序中可能出现的错误，并能根据问题进行学习、拓广、深化；

(3) 学会科学地撰写总结报告，加深对所学知识的理解和掌握，培养表达和思辨能力；

任务：
设计一个学生信息管理系统，内含三大模块：学生模块、教师模块、管理员模块，每个模块拥有不同的权限和功能。需要实现的任务包括：

1.登录系统：账号注册、登录、删改密码功能

2.信息系统：每个学生和教师拥有姓名、ID、电话号码等信息、可以实现对自己信息的修改和对他人信息的查看。

3.班级系统：每个学生可以选择加入不同班级，加入班级后可以查看班级名单和同班同学信息。

4.成绩系统：可细分到不同学期的不同科目。科目拥有学科名绩点，所占学分，分数等数据。每个学期的数据分开存储计算。由教师对管理班级进行添加和删除科目。修改科目后会实时计算该学期的GPA和加权平均分。可以选择通过 学号/GPA/加权平均分 的方式对同班级的同学成绩排序。

5.管理员系统：可以查看该系统内所有数据。拥有查看全体名单，发放教师ID,添加和删除班级、学期等功能

6.文件存储:文件存储和读取功能，向文件里保存数据。

![image](https://user-images.githubusercontent.com/74815734/159161763-4309884e-b68e-48aa-a09b-8c10900101ea.png)
![image](https://user-images.githubusercontent.com/74815734/159161769-d8864189-e82c-4be7-9aec-efd2890949c9.png)
![image](https://user-images.githubusercontent.com/74815734/159161752-daffb77e-ecc1-49a4-8d4c-69cb5c6d2d6e.png)

课程设计总结

对于本次大作业的设计，最终圆满的完成了最初设计的全部功能，从最初的设计到成果的完成耗时近40小时，代码量也写到了1800行，算是一个不小的工程了，自己对结果还是非常满意的。

这次大作业的完成过程中还是有不少困难的，写代码中途也出现不少的阻碍。有时为了调整一个函数的实现需要反复debug几个小时。在我看来，本次设计过程中困难主要体验在类的设计和交互方面。因为本程序的层次比较多，涉及到不同班级，不同学期的管理，因此即使是已经提前设计好了不同类的结构和负责的功能，但在实际写到那部分时还是有很多设计时没有想到的，造成了不少问题。其中令我影响最深刻的是写到“学生加入班级”部分的功能时，设计目标要把这个student类从原classp类内的map中删除，再加入到新的classp类中，但实际写的时候，在删除操作后，有一些指向原来student的指针便会失效，还要找到对应的指针进行修改，这个问题因为最初设计时没有想到，最终花费了较长时间设计和修改。写到UI类时，也会发现很多功能管理类的函数没法实现，最后还要去修改已经本来写好的数据类，造成了很多麻烦。

从上述困难中我得到了教训，在正式敲代码前一定要设计好程序结构，在最初的设计阶段多去思考一些可能存在的问题，并用合理的方式解决它，即“谋定而后动”，不然最后就会出现反复修改的内耗。并且出现bug时多用调试功能，VS的调试功能还是很强大的，帮助我解决不少麻烦。
