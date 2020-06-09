#include<iostream>
#include<string.h>
#define boolean int
#define true 1
#define TRUE 1
#define false 0
#define FALSE 0
using namespace std;
class Student
{
private:
int rollNumber;
char *name;
public:
Student();
~Student();
Student(const Student &);
Student & operator=(Student);
void setRollNumber(int);
int getRollNumber();
void setName(const char *);
void getName(char* &);
};
Student::Student()
{
this->rollNumber=0;
this->name=NULL;
}
Student::~Student()
{
if(this->name!=NULL) delete [] this->name;
}
void Student::setName(const char *name)
{
if(this->name!=NULL) delete[] this->name;
this->name=new char[strlen(name)+1];
strcpy(this->name,name);
}
void Student::getName(char* &name)
{
if(name==NULL) return;
if(this->name==NULL)
{
name=NULL;
return;
}
name=new char[strlen(this->name)+1];
strcpy(name,this->name);
}
void Student::setRollNumber(int rollNumber)
{
this->rollNumber=rollNumber;
}
int Student::getRollNumber()
{
return this->rollNumber;
}
Student::Student(const Student &otherStudent)
{
cout<<"copy constructor is called ."<<endl;
this->rollNumber=0;
this->name=NULL;
this->setRollNumber(otherStudent.rollNumber);
this->setName(otherStudent.name);
}
Student & Student::operator=(Student otherStudent)
{
cout<<"equal function is called ."<<endl;
this->setRollNumber(otherStudent.rollNumber);
this->setName(otherStudent.name);
return *this;
}
class SinglyLinkedListNode
{
private:
Student *student;
SinglyLinkedListNode *next;
SinglyLinkedListNode(Student *);
friend class SinglyLinkedList;
friend class SinglyLinkedListIterator;
};
SinglyLinkedListNode::SinglyLinkedListNode(Student *student)
{ 
this->student=student;
this->next=NULL;
} 
class SinglyLinkedListIterator
{
private:
SinglyLinkedListNode *node;
SinglyLinkedListIterator(SinglyLinkedListNode *);
public:
boolean hasNext();
Student * next();
friend class SinglyLinkedList;
};
SinglyLinkedListIterator::SinglyLinkedListIterator(SinglyLinkedListNode *node)
{ 
this->node=node;
}
boolean SinglyLinkedListIterator::hasNext()
{
return this->node!=NULL;
}
Student * SinglyLinkedListIterator::next()
{ 
if(this->node==NULL) return NULL;
Student *student;
student=this->node->student;
this->node=this->node->next;
return student;
} 
class SinglyLinkedList
{
private:
SinglyLinkedListNode *start;
SinglyLinkedListNode *end;
int size;
public:
SinglyLinkedList();
SinglyLinkedList(const SinglyLinkedList &);
~SinglyLinkedList();
SinglyLinkedList & operator=(SinglyLinkedList);
void add(Student *);
void insert(int,Student *);
Student * remove(int);
void clear();
Student * get(int);
int getSize();
SinglyLinkedListIterator * getIterator();
};
SinglyLinkedList::SinglyLinkedList()
{ 
this->size=0;
this->start=NULL;
this->end=NULL;
}
SinglyLinkedList::SinglyLinkedList(const SinglyLinkedList &otherSinglyLinkedList)
{
}
SinglyLinkedList::~SinglyLinkedList()
{ 
this->clear();
}
SinglyLinkedList & SinglyLinkedList::operator=(SinglyLinkedList otherSinglyLinkedList)
{
}
void SinglyLinkedList::add(Student *student)
{
SinglyLinkedListNode *node;
node=new SinglyLinkedListNode(student);
if(this->start==NULL)
{ 
this->start=node;
this->end=node;
} 
else
{ 
end->next=node;
end=node;
} 
this->size++;
}
Student * SinglyLinkedList::get(int index)
{ 
if(index<0|| index>=size) return NULL;
SinglyLinkedListNode *node;
node=this->start;
int x;
x=0;
while(x<index)
{
node=node->next;
x++;
}
return node->student;
} 
int SinglyLinkedList::getSize()
{
return this->size;
}
void SinglyLinkedList::insert(int position,Student *student)
{ 
if(position<0) position=0;
if(position>this->size) position=this->size;
if(position==this->size)
{ 
this->add(student);
return;
}
SinglyLinkedListNode *node;
node=new SinglyLinkedListNode(student);
if(position==0)
{
node->next=this->start;
this->start=node;
} 
else
{
SinglyLinkedListNode *t,*k;
int x;
t=this->start;
x=0;
while(x<position)
{
k=t;
t=t->next;
x++;
}
node->next=t;
k->next=node;
} 
this->size++;
}
Student * SinglyLinkedList::remove(int position)
{ 
if(position<0|| position>=this->size) return NULL;
Student *student;
SinglyLinkedListNode *t;
if(this->size==1)
{ 
t=this->start;
student=t->student;
this->start=NULL;
this->end=NULL;
delete t;
this->size=0;
return student;
}
SinglyLinkedListNode *k;
t=this->start;
int x;
x=0;
while(x<position)
{
k=t;
t=t->next;
x++;
} 
if(this->start==t)
{ 
this->start=this->start->next;
student=t->student;
delete t;
this->size--;
return student;
} 
if(this->end==t)
{ 
end=k;
end->next=NULL;
student=t->student;
delete t;
this->size--;
return student;
}
k->next=t->next;
student=t->student;
delete t;
this->size--;
return student;
}
void SinglyLinkedList::clear()
{
while(this->size>0) this->remove(0);
}
SinglyLinkedListIterator * SinglyLinkedList::getIterator()
{
return new SinglyLinkedListIterator(this->start);
} 
class Queue
{
private:
SinglyLinkedList list;
public:
Queue();
Queue(const Queue &);
~Queue();
Queue & operator=(Queue);
void add(Student *);
Student * remove();
boolean isEmpty();
Student * elementAtTop();
int getSize();
void clear();
};
Queue::Queue()
{ 
}
Queue::Queue(const Queue &otherQueue)
{ 
this->list=otherQueue.list;
}
Queue::~Queue()
{
}
Queue & Queue::operator=(Queue otherQueue)
{ 
this->list=otherQueue.list;
}
void Queue::add(Student *student)
{ 
list.add(student);
}
Student * Queue::remove()
{ 
if(this->isEmpty()) return NULL;
Student *student;
student=list.remove(0);
return student;
}
boolean Queue::isEmpty()
{
return this->list.getSize()==0;
}
Student * Queue::elementAtTop()
{ 
if(this->isEmpty()) return NULL;
Student *student;
student=list.get(0);
return student;
} 
int Queue::getSize()
{
return this->list.getSize();
}
void Queue::clear()
{
this->list.clear();
}
int main()
{
Student *s1;
s1=new Student();
s1->setRollNumber(101);
s1->setName("Mahesh");
Student *s2;
s2=new Student();
s2->setRollNumber(102);
s2->setName("Lalita");
Student *s3;
s3=new Student();
s3->setRollNumber(103);
s3->setName("Rohit");
Queue que;
que.add(s1);
que.add(s2);
que.add(s3);
Student *s;
int r;
char *n;
while(que.isEmpty()==false)
{
s=que.remove();
r=s->getRollNumber();
s->getName(n);
cout<<"Roll number : "<<r<<", Name : "<<n<<endl;
delete [] n;
}
return 0;
}

