#include<iostream>
using namespace std;
#include<string.h>
#define boolean int
#define true 1
#define false 0
#define TRUE 1
#define FALSE 0
class Student
{
private:
int rollNumber; 
char *name;
public:
Student();
Student(const Student &);
Student & operator=(Student);
~Student();
void setRollNumber(int);
int getRollNumber();
void setName(const char *);
void getName(char * &);
};
Student::Student()
{ 
cout<<"Default constructor got invoked"<<endl;
this->rollNumber=0;
this->name=NULL;
}
Student::Student(const Student &otherStudent)
{ 
cout<<"Copy constructor got invoked"<<endl;
this->rollNumber=0;
this->name=NULL;
this->setRollNumber(otherStudent.rollNumber);
this->setName(otherStudent.name);
}
Student & Student::operator=(Student otherStudent)
{ 
cout<<"= function got invoked"<<endl;
setRollNumber(otherStudent.rollNumber);
setName(otherStudent.name);
return *this;
}
Student::~Student()
{ 
if(this->name!=NULL) delete [] this->name;
}
void Student::setRollNumber(int rollNumber)
{ 
this->rollNumber=rollNumber;
} 
int Student::getRollNumber()
{
return this->rollNumber;
}
void Student::setName(const char *name)
{ 
if(this->name!=NULL)
{
delete [] this->name;
this->name=NULL;
} 
if(name==NULL) return;
this->name=new char[strlen(name)+1];
strcpy(this->name,name);
}
void Student::getName(char * &name)
{ 
if(this->name==NULL)
{
name=NULL;
return;
}
name=new char[strlen(this->name)+1];
strcpy(name,this->name);
} 


class DoublyLinkedListNode
{
private:
Student *student;
DoublyLinkedListNode *next;
DoublyLinkedListNode *previous;
DoublyLinkedListNode(Student *);
friend class DoublyLinkedList;
friend class DoublyLinkedListIterator;
};
DoublyLinkedListNode::DoublyLinkedListNode(Student *student)
{ 
this->student=student;
this->next=this->previous=NULL;
} 
class DoublyLinkedListIterator
{
private:
int iteratorType;
DoublyLinkedListNode *node;
DoublyLinkedListIterator(DoublyLinkedListNode *,int);
public:
boolean hasNext();
boolean hasPrevious();
Student * next();
Student * previous();
static int TOP_TO_BOTTOM;
static int BOTTOM_TO_TOP;
static int SCROLLABLE;
friend class DoublyLinkedList;
};
int DoublyLinkedListIterator::TOP_TO_BOTTOM=1;
int DoublyLinkedListIterator::BOTTOM_TO_TOP=2;
int DoublyLinkedListIterator::SCROLLABLE=3;
DoublyLinkedListIterator::DoublyLinkedListIterator(DoublyLinkedListNode *node,int iteratorType)
{ 
this->node=node;
this->iteratorType=iteratorType;
}


boolean DoublyLinkedListIterator::hasNext()
{ 
if(this->node==NULL || this->iteratorType==BOTTOM_TO_TOP) return false;
return true;
}
boolean DoublyLinkedListIterator::hasPrevious()
{ 
if(this->node==NULL || this->iteratorType==TOP_TO_BOTTOM) return false;
return true;
}
Student * DoublyLinkedListIterator::next()
{ 
if(this->node==NULL || this->iteratorType==BOTTOM_TO_TOP) return NULL;
Student *student=this->node->student;
this->node=this->node->next;
return student;
}
Student * DoublyLinkedListIterator::previous()
{ 
if(this->node==NULL || this->iteratorType==TOP_TO_BOTTOM) return NULL;
Student *student=this->node->student;
this->node=this->node->previous;
return student;
} 
class DoublyLinkedList
{
private:
DoublyLinkedListNode *start;
DoublyLinkedListNode *end;
int size;
public:
DoublyLinkedList();
DoublyLinkedList(const DoublyLinkedList &);
~DoublyLinkedList();
DoublyLinkedList & operator=(DoublyLinkedList);
void add(Student *);
void insert(int,Student *);
Student * remove(int);
void clear();
Student * get(int);
int getSize();
DoublyLinkedListIterator * getIterator();
DoublyLinkedListIterator * getIterator(int);
};
DoublyLinkedList::DoublyLinkedList()
{ 
this->size=0;
this->start=this->end=NULL;
}
DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList &otherDoublyLinkedList)
{ 
this->size=0;
this->start=this->end=NULL;
DoublyLinkedListNode *node=otherDoublyLinkedList.start;
while(node!=NULL)
{ 
this->add(node->student);
node=node->next;
}
}
DoublyLinkedList::~DoublyLinkedList()
{ 
this->clear();
}
DoublyLinkedList & DoublyLinkedList::operator=(DoublyLinkedList otherDoublyLinkedList)
{ 
this->clear();
DoublyLinkedListNode *node=otherDoublyLinkedList.start;
while(node!=NULL)
{ 
this->add(node->student);
node=node->next;
}
}
void DoublyLinkedList::add(Student *student)
{
DoublyLinkedListNode *node;
node=new DoublyLinkedListNode(student);
if(this->start==NULL)
{ 
this->start=this->end=node;
} 
else
{ 
end->next=node;
node->previous=end;
end=node;
} this->size++;
}
Student * DoublyLinkedList::get(int index)
{ 
if(index<0|| index>=this->size) return NULL;
DoublyLinkedListNode *node;
int x;
if(index<this->size/2)
{
x=0;
node=this->start;
while(x<index)
{
node=node->next;
x++;
}
} 
else
{
x=size-index;
node=this->end;
while(x>1)
{
node=node->previous;
x--;
}
}
return node->student;
} 
int DoublyLinkedList::getSize()
{
return this->size;
}
void DoublyLinkedList::insert(int position,Student *student)
{ 
if(position<0) position=0;
if(position>this->size) position=this->size;
if(position==this->size)
{ 
this->add(student);
return;
}
DoublyLinkedListNode *node;
node=new DoublyLinkedListNode(student);
if(position==0)
{
node->next=this->start;
this->start->previous=node;
this->start=node;
this->size++;
return;
}
DoublyLinkedListNode *t;
int x;
if(position<this->size/2)
{
for(t=this->start,x=0;x<position;x++,t=t->next);
} 
else
{
for(t=this->end,x=this->size-position;x>1;x--,t=t->previous);
}
node->next=t;
node->previous=t->previous;
t->previous->next=node;
t->previous=node;
this->size++;
}
Student * DoublyLinkedList::remove(int position)
{ 
if(position<0|| position>=this->size) return NULL;
DoublyLinkedListNode *t;
int x;
if(position<this->size/2)
{
for(x=0,t=this->start;x<position;x++,t=t->next);
} 
else
{
for(x=this->size-position,t=this->end;x>1;t=t->previous,x--);
}
Student *student=t->student;
if(this->start==this->end)
{ 
this->start=this->end=NULL;
this->size=0;
delete t;
return student;
} 
if(t==this->start)
{ 
this->start=this->start->next;
this->start->previous=NULL;
this->size--;
delete t;
return student;
} 
if(t==this->end)
{ 
this->end=this->end->previous;
this->end->next=NULL;
this->size--;
delete t;
return student;
} 
t->next->previous=t->previous;
t->previous->next=t->next;
this->size--;
delete t;
return student;
}
void DoublyLinkedList::clear()
{
while(this->size>0) this->remove(0);
}
DoublyLinkedListIterator * DoublyLinkedList::getIterator()
{
return this->getIterator(DoublyLinkedListIterator::TOP_TO_BOTTOM);
}
DoublyLinkedListIterator * DoublyLinkedList::getIterator(int iteratorType)
{ 
if(iteratorType==DoublyLinkedListIterator::TOP_TO_BOTTOM)
{
return new DoublyLinkedListIterator(this->start,DoublyLinkedListIterator::TOP_TO_BOTTOM);
} 
if(iteratorType==DoublyLinkedListIterator::BOTTOM_TO_TOP)
{
return new DoublyLinkedListIterator(this->end,DoublyLinkedListIterator::BOTTOM_TO_TOP);
} 
if(iteratorType==DoublyLinkedListIterator::SCROLLABLE)
{
return new DoublyLinkedListIterator(this->start,DoublyLinkedListIterator::SCROLLABLE);
}
return NULL;
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
Student *s4;
s4=new Student();
s4->setRollNumber(105);
s4->setName("Mohit");
Student *s5;
s5=new Student();
s5->setRollNumber(106);
s5->setName("Tina");
DoublyLinkedList dll;
dll.add(s1);
dll.add(s2);
dll.add(s3);
dll.add(s4);
dll.add(s5);
cout<<"Size of dll : "<<dll.getSize()<<endl;
Student *s;
char *n;
int r;
cout<<"Traversing top to bottom"<<endl;
for(int i=0;i<dll.getSize();i++)
{
s=dll.get(i);
r=s->getRollNumber();
s->getName(n);
cout<<"Roll number "<<r<<", Name "<<n<<endl;
delete [] n;
} 
cout<<"Traversing bottom to top"<<endl;
for(int i=dll.getSize()-1;i>=0;i--)
{
s=dll.get(i);
r=s->getRollNumber();
s->getName(n);
cout<<"Roll number "<<r<<", Name "<<n<<endl;
delete [] n;
} 
cout<<"Iterating using top-bottom iterator"<<endl;
DoublyLinkedListIterator *iterator;
iterator=dll.getIterator();
while(iterator->hasNext())
{
s=iterator->next();
r=s->getRollNumber();
s->getName(n);
cout<<"Roll number "<<r<<", Name "<<n<<endl;
delete [] n;
} 
cout<<"Iterating using bottom-top iterator"<<endl;
iterator=dll.getIterator(DoublyLinkedListIterator::BOTTOM_TO_TOP);
while(iterator->hasPrevious())
{
s=iterator->previous();
r=s->getRollNumber();
s->getName(n);
cout<<"Roll number "<<r<<", Name "<<n<<endl;
delete [] n;
} 
int ii=0;
cout<<"Iterating using scrollable iterator"<<endl;
iterator=dll.getIterator(DoublyLinkedListIterator::SCROLLABLE);
while(iterator->hasNext())
{ 
ii++;
s=iterator->next();
r=s->getRollNumber();
s->getName(n);
cout<<"Roll number "<<r<<", Name "<<n<<endl;
delete [] n;
if(ii==3)
{
s=iterator->previous();
r=s->getRollNumber();
s->getName(n);
cout<<"Roll number "<<r<<", Name "<<n<<endl;
delete n;
}
}
delete s1;
delete s2;
delete s3;
delete s4;
delete s5;
return 0;
}

