#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "error.h"
using namespace std;
enum Datatype {NONE,INT,FLOAT,BOOL,A,REG};
struct RegG
{
        bool bool_valRegG;
        int int_valRegG;
        float float_valRegG;
        int address_valRegG;
        Datatype type_regG;
};
struct StaticM
{
        bool boolStaticM;
        int int_valStaticM;
        float floatStaticM;
        Datatype type_staticM;
};
template <class T >
class IList
{
 public :
virtual void add (T e) = 0;
virtual void add ( int index , T e) = 0;
virtual T removeAt (int index ) = 0;
 virtual bool removeItem (T item ) = 0;
 virtual bool empty () = 0;
 virtual int size () = 0;
 virtual void clear () = 0;
 virtual T get (int index ) = 0;
 virtual void set ( int index , T e) = 0;
 virtual int indexOf (T item ) = 0;
 virtual bool contains ( T item ) = 0;

 };
template <class T >
class DLinkedList : public IList<T>
{
public:
        class Node; // Forward declaration

protected:
        Node *head;
        Node *tail;
        int count;

public:
        DLinkedList() : head(NULL), tail(NULL), count(0){};
        virtual void add(T element)
        {
                // chua co phan tu nao
                if (this->count == 0)
                {
                        Node *tmp = new Node(element);
                        this->head = this->tail = tmp;
                        this->count++;
                }
                // th co phan tu
                else
                {
                        Node *tmp = new Node(element);
                        this->tail->next = tmp;
                        tmp->prev = this->tail;
                        this->tail = tmp;
                        this->count++;
                }
        }

        virtual void add(int index, T element)
        {
                // check index
                if (index < 0 || index > this->count)
                        throw std ::out_of_range(" index error");
                // execution
                else
                {
                        // chua co phan tu nao
                        if (this->count == 0)
                        {
                                this->add(element);
                        }
                        // add o dau
                        else if (index == 0)
                        {
                                Node *tmp = new Node(element);
                                this->head->prev = tmp;
                                tmp->next = this->head;
                                this->head = tmp;
                                this->count++;
                        }
                        // add o cuoi
                        else if (index == this->count)
                        {
                                this->add(element);
                        }
                        //add o giua
                        else
                        {
                                Node *tmp = new Node(element);
                                Node *tmp_index = this->head;
                                // chay toi cho index
                                for (int i = 0; i < index; i++)
                                {
                                        tmp_index = tmp_index->next;
                                }
                                tmp->prev = tmp_index->prev;
                                tmp_index->prev->next = tmp;
                                tmp->next = tmp_index;
                                tmp_index->prev = tmp;
                                this->count++;
                        }
                }
        }

        virtual  T removeAt(int index)
        {
                // check index
                if (index < 0 || index >= this->count)
                        throw std ::out_of_range(" index error");
                else
                {
                        T element = 0;
                        // list co 1 phan tu
                        if (this->count == 1)
                        {
                                Node *tmp = this->head;
                                this->head = nullptr;
                                this->tail = nullptr;
                                element = tmp->data;
                                delete tmp;
                                this->count--;
                        }
                        // xoa o dau
                        else if (index == 0)
                        {
                                Node *tmp = this->head;
                                this->head = this->head->next;
                                this->head->prev = nullptr;
                                tmp->next = nullptr;
                                element = tmp->data;
                                delete tmp;
                                this->count--;
                        }
                        // xoa o cuoi
                        else if (index == this->count - 1)
                        {
                                Node *tmp = this->tail;
                                this->tail = this->tail->prev;
                                this->tail->next = nullptr;
                                tmp->prev = nullptr;
                                element = tmp->data;
                                delete tmp;
                                this->count--;
                        }
                        // xoa o giua
                        else
                        {
                                Node *tmp = this->head;
                                for (int i = 0; i < index; i++)
                                {
                                        tmp = tmp->next;
                                }
                                tmp->prev->next = tmp->next;
                                tmp->next->prev = tmp->prev;
                                tmp->next = nullptr;
                                tmp->prev = nullptr;
                                element = tmp->data;
                                delete tmp;
                                this->count--;
                        }
                        return element;
                }
        }

        virtual bool removeItem(T item)
        {
                // list khong co phan tu nao
                if (this->count == 0)
                        return false;
                else
                {
                        Node *tmp = this->head;
                        for (int i = 0; i < this->count; i++)
                        {
                                if (tmp->data == item)
                                {
                                        this->removeAt(i);
                                }
                                return true;
                        }

                        return false;
                }
        }

        virtual bool empty()
        {

                return this->count == 0;
        }

        virtual int size()
        {

                return this->count;
        }

        virtual T get(int index)
        {
                // check index
                if (index < 0 || index >= this->count)
                        throw std ::out_of_range(" index error");
                else
                {
                        Node *tmp = this->head;
                        for (int i = 0; i < index; i++)
                        {
                                tmp = tmp->next;
                        }
                        return tmp->data;
                }
        }

        virtual void set(int index, T element)
        {
                if (index < 0 || index >= this->count)
                        throw std ::out_of_range(" index error");
                else
                {
                        Node *tmp = this->head;
                        for (int i = 0; i < index; i++)
                        {
                                tmp = tmp->next;
                        }
                        tmp->data = element;
                }
        }

        virtual int indexOf(T item)
        {

                if (this->count == 0)
                        return -1;
                else
                {
                        Node *tmp = this->head;
                        for (int i = 0; i < this->count; i++)
                        {
                                if (tmp->data == item)
                                {
                                        return i;
                                }
                                else
                                        tmp = tmp->next;
                        }

                        return -1;
                }
        }

        virtual bool contains(T item)
        {
                if (this->count == 0)
                        return false;
                else
                {
                        Node *tmp = this->head;
                        for (int i = 0; i < this->count; i++)
                        {
                                if (tmp->data == item)
                                {
                                        return true;
                                }
                                else
                                        tmp = tmp->next;
                        }

                        return false;
                }
        }

        virtual void clear()
        {
                while (this->count != 0)
                {
                        this->removeAt(this->count - 1);
                        this->count--;
                }
                this->head = this->tail = nullptr;
        }

        
public:
        class Node
        {
        public:
                T data;
                Node *next;
                Node *prev;

        public:
                Node() : data(0), next(NULL), prev(NULL){};
                Node(T data) : data(data), next(NULL), prev(NULL){};
        };
}; 
class VM
{
public:
    class CPU;
    class StaticMemmory;
    class CodeMemmory;
    class IntStack;
private:
    IntStack *stack;
    CPU *cpu;
    StaticMemmory *staticM;
    CodeMemmory *codeM;
public:
   VM(){
      this->stack= new IntStack;
      this->staticM= new StaticMemmory;
      this->cpu=new CPU;
      this->codeM=new CodeMemmory;

    }
    
void run(string filename) // RUN chuong trinh
  {
    // read file and stored in code memory
    ifstream file(filename);
    string *splited= new string[3];
    int i=0;
    if (file.is_open()) {
    string line;
    while (getline(file, line)) {
        // using printf() in all tests for consistency
        this->codeM->codeMemmory[i]=line;
        this->checkErrorload(this->codeM->codeMemmory[i],splited,i);
        i++;
    }
    file.close();
}
   /* while (getline (myfile,this->codeM->codeMemmory[i])) 
    {
        // check lenh co hop le hay khong checkError
          // check co dung cu phap co ban nhat hay khong (cu phap , not chinh ta lenh)
          this->checkErrorload(this->codeM->codeMemmory[i],splited,i);

        i++;
        ///// CHECK IF I > 655356 THROW ERROR ?? // khong checkloi nay
    }
/*    while(i>0)
    {
        // Read lenh tai dia chi IP
        
        this->readInstruction(this->codeM->codeMemmory->get(this->cpu->IP),splited);
        // thuc thi
        this->execution(splited,i);
        // tra ve dia chi luu vao stack

          // if stack day THROW ERROR StackFull(address) address cua bo nho lenh (IP)
             if (this->stack->fullStack()) throw StackFull(this->cpu->IP);
             else
             {
                 this->stack->push(this->cpu->IP);
             }
        
        // tang IP len 1
        this->cpu->IP+=1;
        i--;

    }*/
  }
bool isCode(string code) // check " MA CODE" co hop le hay khong
  { 
      string codeID[16]={"Add","Minus","Mul","Div","CmpEQ","CmpNE","CmpLT","CmpLE","CmpGT","CmpGE","And","Or","Move","Load","Store","JumpIf"};
      for(int i=0;i<16;i++)
      {
          if (code==codeID[i]) 
          {
                return 1;
          }
      }
      return 0;
  }
void isSrc(string src_check,int address) //RegG &src)
  {
    regex e("R[[:d:]]+|[[:d:]]+|[[:d:]]+[.][[:d:]]+|true|false|[[:d:]]+A"); // hang nguyen hang float la ntn
    if (!regex_match(src_check, e)) throw InvalidInstruction(address);
    else {
            while(true)
            {
                    // check cu phap khi src la thanh ghi
                regex e("R[[:d:]]+");
                if (regex_match(src_check, e))
                {
                        if (src_check[1]=='0' && src_check.length()!=2) throw InvalidOperand(address);
                        int src_num= stoi(src_check.substr(1));
                        if (src_num>0 && src_num < 16) 
                        {
                              /*  src.type_regG=this->cpu->R_general[src_num].type_regG;
                                if (src.type_regG==INT) src.int_valRegG=this->cpu->R_general[src_num].int_valRegG;
                                else if (src.type_regG==FLOAT) src.float_valRegG=this->cpu->R_general[src_num].float_valRegG;
                                else if (src.type_regG==BOOL) src.bool_valRegG=this->cpu->R_general[src_num].bool_valRegG;
                                else if (src.type_regG==A) src.address_valRegG=this->cpu->R_general[src_num].address_valRegG;*/
                             //   src.type_regG= REG;
                             //   src.address_valRegG=src_num;
                        }
                        else throw InvalidOperand(address);
                        break;
                }
                //  check cu phap khi src la hang int
                regex e_int("[[:d:]]+"); // hang int co dang gi ?? => sua dk e
                if(regex_match(src_check, e_int)) 
                {
                        if (src_check[0]=='0'&& src_check.length()!=1) throw InvalidOperand(address); // check hang int
                        else
                        {
                              //  src.int_valRegG= stoi(src_check);
                              //  src.type_regG=INT;
                        }
                        break;
                }
                //  check cu phap khi src la hang float
                regex e_float("[[:d:]]+[.][[:d:]]+"); // hang float co dang gi ??
                if(regex_match(src_check, e_float)) 
                {
                      //  src.type_regG=FLOAT;
                      //  src.float_valRegG=stof(src_check);
                        break;
                }
                
                //  check cu phap khi src la hang bool
                if (src_check=="false") 
                {
                     //   src.type_regG= BOOL;
                     //   src.bool_valRegG = 0;
                        break;
                }
                else if (src_check=="true")
                {
                     //   src.type_regG= BOOL;
                     //   src.bool_valRegG = 1;
                        break;
                }
                //  check cu phap khi src la hang address
                regex e_address("[[:d:]]+A"); // hang address co dang gi ??
                if(regex_match(src_check, e_address)) 
                {
                        if (src_check[0]=='0' && src_check.length()!=2) throw InvalidOperand(address); // check hang int
                        else
                        {
                            //    src.address_valRegG =stoi(src_check);
                            //    src.type_regG=A;
                        }
                        break;
                }
            }
            
            

            
    }
  }
void isDest(string dest_check,int address)//, RegG &dest)
  {
    regex e("R[[:d:]]+");
    if (!regex_match(dest_check, e)) throw InvalidOperand(address) ;
    else{
            if (dest_check[1]=='0' && dest_check.length()!=2) throw InvalidOperand(address);
            int dest_num= stoi(dest_check.substr(1));
            if (dest_num>0 && dest_num < 16) 
            {
                   /* dest.type_regG=this->cpu->R_general[dest_num].type_regG;  // tinh gia tri cua thanh ghi
                    if (dest.type_regG==INT) dest.int_valRegG=this->cpu->R_general[dest_num].int_valRegG;
                    else if (dest.type_regG==FLOAT) dest.float_valRegG=this->cpu->R_general[dest_num].float_valRegG;
                    else if (dest.type_regG==BOOL) dest.bool_valRegG=this->cpu->R_general[dest_num].bool_valRegG;
                    else if (dest.type_regG==A) dest.address_valRegG=this->cpu->R_general[dest_num].address_valRegG;*/
               // dest.type_regG=REG;
               // dest.address_valRegG=dest_num;
            }
            else throw InvalidOperand(address);
    } 

  }
void isInstruction(string string_check,string *splited,int address)//,RegG &dest, RegG &src)
    {
        string code= splited[0];

        if (code=="Not" ||code=="Input") 
        {
            regex e("[[:alpha:]]+[[:space:]][[:alnum:]]+");
            if (regex_match(string_check, e))
            {
                 // code dest
                 isDest(splited[1],address);//,dest);
            }
            else throw InvalidInstruction(address);
        }
        else if (code=="Jump" ||code=="Call"||code=="Output")  // code src(.)
        {
            regex e("[[:alpha:]]+[[:space:]][^ ]+");
            if (regex_match(string_check, e))
            {
                 // code src
                isSrc(splited[1],address);//,src);
            }
            else throw InvalidInstruction(address);
        }
        else if (code=="Return"|| code=="Halt") 
        {
            regex e("[[:alpha:]]+");
            if (!regex_match(string_check, e)) throw InvalidInstruction(address);
        }
        else if (this->isCode(code)) 
        {
            isSrc(splited[2],address);//,src);
            isDest(splited[1],address);//,dest);
        }
        else throw InvalidInstruction(address);
        
  }    
bool isBasicIns(string string_check)
{
    regex e("[[:alpha:]]+[[:space:]][[:alnum:]]+,[[:space:]][^ ]+|[[:alpha:]]+[[:space:]][[:alnum:]]+|[[:alpha:]]+|[[:alpha:]]+[[:space:]][^ ]+");
    return regex_match(string_check, e);
}
void split(string string_to_split, string *splited)
  {
    int num_operand=0;
    regex rgx("\\s+|,\\s+");
    sregex_token_iterator iter(string_to_split.begin(),string_to_split.end(),rgx,-1);
    sregex_token_iterator end;
    for ( ; iter != end && num_operand<3; ++iter)
    {
        splited[num_operand]=*iter;
        num_operand++; 
    }

  }
void checkErrorload(string instruction,string *splited, int address)//,RegG &dest, RegG &src)
{
        // check dung format co ban chua
        if (!isBasicIns(instruction)) throw InvalidInstruction(address);
        // check code tung ma lenh
        else{
                // split instruction
                split(instruction,splited);
                // check ma lenh // check operand
                isInstruction(instruction,splited,address);//,dest,src);
        }
}    
public:
class CPU
{
    public:
    int IP;
    RegG R_general[15];
    public:
    CPU()
    {
        this->IP=0;
        for (int i = 0; i < 15; i++)
        {
                this->R_general[i].type_regG=NONE;
        }
        

    }

};
class StaticMemmory
{
    public:
    StaticM *staticMemmory;// T only bool,int,float
    public:
    StaticMemmory()
    {
        this->staticMemmory=new StaticM[65536] ;
    }
};
class IntStack
{
private:
        DLinkedList<int> *list;

public:
        IntStack()
        {
                this->list = new DLinkedList<int>();
        }
        ~IntStack()
        {
                this->list->clear();
                delete list;
        }
        void push(int element)
        {
                this->list->add(element);
        }
        int pop()
        {
                int size = this->list->size();
                return this->list->removeAt(size - 1);
        }
        int peek()
        {
                int size = this->list->size();
                return this->list->get(size - 1);
        }
        bool empty()
        {
                return this->list->empty();
        }
        bool contains(int element)
        {
                return this->list->contains(element);
        }
        bool fullStack()
        {
            if (this->list->size()==65536) return 1;
            else return 0;
        }
};
class CodeMemmory
{
        public:
        string *codeMemmory;
        public:
        CodeMemmory()
        {
                this->codeMemmory=new string[65536];
        }
};

};
void test(string filename) {
    VM *vm = new VM();
    try {
        vm->run(filename);
    }
    catch (exception& e) {
        cout << e.what();
    }
    delete vm;
}

int main()
{
      test("test.txt");
   //test("prog1.txt");
}