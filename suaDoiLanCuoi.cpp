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
//        cout<<"i="<< i<<endl;
//        cout<< "IP= "<<this->cpu->IP<<endl;
        while(this->cpu->IP< i)
        {
                split(this->codeM->codeMemmory[this->cpu->IP],splited);
                string code = splited[0];
                //cout<< "\ncode="<< code ;
                // thuc thi

                if (code == "Add") this->add(splited,this->cpu->IP);
                else if (code=="Minus") this->minus(splited,this->cpu->IP);
                else if (code=="Mul") this->mul(splited,this->cpu->IP);
                else if (code == "Div") this->mul(splited,this->cpu->IP);

                else if (code == "CmpEQ") this->CmpEQ(splited,this->cpu->IP);
                else if (code == "CmpNE") this->CmpNE(splited,this->cpu->IP);
                else if (code == "CmpLT") this->CmpLT(splited,this->cpu->IP);
                else if (code == "CmpGT") this->CmpGT(splited,this->cpu->IP);
                else if (code == "CmpGE") this->CmpGE(splited,this->cpu->IP);

                else if (code == "Not") this->Not(splited,this->cpu->IP);
                else if (code == "And") this->And(splited,this->cpu->IP);
                else if (code == "Or") this->Or(splited,this->cpu->IP);

                else if (code == "Move") this->Move(splited,this->cpu->IP);
                else if (code == "Load") this->Load(splited,this->cpu->IP);
                else if (code == "Store") this->Store(splited,this->cpu->IP);

                else if (code == "Jump") this->Jump(splited,this->cpu->IP,i);
                else if (code == "JumpIf") this->JumIf(splited,this->cpu->IP,i);
                else if (code == "Call") this->Call(splited,this->cpu->IP,i);
                else if (code == "Return") this->Return(splited,this->cpu->IP);
                else if (code == "Halt") this->Halt(i);

                else if (code == "Input") this->Input(splited,this->cpu->IP);
                else if (code == "Output") this->Output(splited,this->cpu->IP);
                // tra ve dia chi luu vao stack
                // if stack day THROW ERROR StackFull(address) address cua bo nho lenh (IP)
                if (this->stack->fullStack()) throw StackFull(this->cpu->IP);
                else
                {
                        this->stack->push(this->cpu->IP);
                }
        
                // tang IP len 1
                this->cpu->IP+=1;

        }
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
                        if (src_check[1]=='0') throw InvalidOperand(address);
                        int src_num= stoi(src_check.substr(1));
                        if (src_num>0 && src_num < 16) 
                        {
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
            if (dest_check[1]=='0') throw InvalidOperand(address);
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

// EXECUTION
void exchangeDest(string ex_dest, RegG &dest)
{
        int dest_num= stoi(ex_dest.substr(1))-1;
        dest.type_regG=this->cpu->R_general[dest_num].type_regG;  // tinh gia tri cua thanh ghi
        if (dest.type_regG==INT) dest.int_valRegG=this->cpu->R_general[dest_num].int_valRegG;
        else if (dest.type_regG==FLOAT) dest.float_valRegG=this->cpu->R_general[dest_num].float_valRegG;
        else if (dest.type_regG==BOOL) dest.bool_valRegG=this->cpu->R_general[dest_num].bool_valRegG;
        else if (dest.type_regG==A) dest.address_valRegG=this->cpu->R_general[dest_num].address_valRegG;

}
void exChangeSrc(string ex_src, RegG &src)
{
        // src la General Register
        regex e("R[[:d:]]+");
        if (regex_match(ex_src, e))
        {
                int src_num= stoi(ex_src.substr(1))-1;
                src.type_regG= REG;
                src.address_valRegG=src_num;
                return;
        }
        // src la const int
        regex e_int("[[:d:]]+"); // hang int co dang gi ?? => sua dk e
        if(regex_match(ex_src, e_int)) 
        {
                src.int_valRegG= stoi(ex_src);
                src.type_regG=INT;
                return;
        }
        //  check cu phap khi src la hang float
        regex e_float("[[:d:]]+[.][[:d:]]+"); // hang float co dang gi ??
        if(regex_match(ex_src, e_float)) 
        {
                src.type_regG=FLOAT;
                src.float_valRegG=stof(ex_src);
                return;
        }
        //  check cu phap khi src la hang bool
                if (ex_src=="false") 
                {
                src.type_regG= BOOL;
                src.bool_valRegG = false;
                        return;
                }
                else if (ex_src=="true")
                {
                src.type_regG= BOOL;
                src.bool_valRegG = true;
                        return;
                }
                //  check cu phap khi src la hang address
                regex e_address("[[:d:]]+A"); // hang address co dang gi ??
                if(regex_match(ex_src, e_address)) 
                {
                        src.address_valRegG =stoi(ex_src);
                        src.type_regG=A;
                        return;
                }

}

        // exeArithmetic
void add(string *splited,int address)
{
        // Add dest, src: dest = dest + src
        RegG dest,src;
        int dest_num=stoi(splited[1].substr(1))-1;
        exchangeDest(splited[1],dest); // doi ra gia tri cho dest
        exChangeSrc(splited[2],src);   // doi ra gia tri cho src
        // if Src la thanh ghi
        if (src.type_regG==REG) 
        {
                exchangeDest(splited[2],src);
        }
        if ((src.type_regG!= INT && src.type_regG!=FLOAT) || (dest.type_regG!= INT && dest.type_regG!=FLOAT)) throw TypeMismatch(address);
        else
        {
                if (src.type_regG==INT && dest.type_regG==INT)
                {
                        this->cpu->R_general[dest_num].type_regG=INT;
                        this->cpu->R_general[dest_num].int_valRegG= dest.int_valRegG+ src.int_valRegG;
                }
                else 
                {
                        this->cpu->R_general[dest_num].type_regG=FLOAT;
                        if (src.type_regG==INT && dest.type_regG== FLOAT) this->cpu->R_general[dest_num].float_valRegG= src.int_valRegG + dest.float_valRegG;
                        else if (src.type_regG==FLOAT && dest.type_regG== INT) this->cpu->R_general[dest_num].float_valRegG= src.float_valRegG + dest.int_valRegG;
                        else if (src.type_regG==FLOAT && dest.type_regG== FLOAT) this->cpu->R_general[dest_num].float_valRegG= src.float_valRegG + dest.float_valRegG;                        
                }

                
                
        }

        
        
}
void minus(string *splited,int address)
{
        //Minus dest, src: dest = dest - rc
        RegG dest,src;
        int dest_num=stoi(splited[1].substr(1))-1;
        exchangeDest(splited[1],dest); // doi ra gia tri cho dest
        exChangeSrc(splited[2],src);   // doi ra gia tri cho src
        // if Src la thanh ghi
        if (src.type_regG==REG) 
        {
                exchangeDest(splited[2],src);
        }
        if ((src.type_regG!= INT && src.type_regG!=FLOAT) || (dest.type_regG!= INT && dest.type_regG!=FLOAT)) throw TypeMismatch(address);
        else
        {
                if (src.type_regG==INT && dest.type_regG==INT)
                {
                        this->cpu->R_general[dest_num].type_regG=INT;
                        this->cpu->R_general[dest_num].int_valRegG= dest.int_valRegG- src.int_valRegG;
                }
                else 
                {
                        this->cpu->R_general[dest_num].type_regG=FLOAT;
                        if (src.type_regG==INT && dest.type_regG== FLOAT) this->cpu->R_general[dest_num].float_valRegG= src.int_valRegG - dest.float_valRegG;
                        else if (src.type_regG==FLOAT && dest.type_regG== INT) this->cpu->R_general[dest_num].float_valRegG= src.float_valRegG - dest.int_valRegG;
                        else if (src.type_regG==FLOAT && dest.type_regG== FLOAT) this->cpu->R_general[dest_num].float_valRegG= src.float_valRegG - dest.float_valRegG;                        
                }

                
                
        }

}
void mul(string *splited,int address)
{
        //Mul dest, src: dest = dest * src
        RegG dest,src;
        int dest_num=stoi(splited[1].substr(1))-1;
        exchangeDest(splited[1],dest); // doi ra gia tri cho dest
        exChangeSrc(splited[2],src);   // doi ra gia tri cho src
        // if Src la thanh ghi
        if (src.type_regG==REG) 
        {
                exchangeDest(splited[2],src);
        }
        if ((src.type_regG!= INT && src.type_regG!=FLOAT) || (dest.type_regG!= INT && dest.type_regG!=FLOAT)) throw TypeMismatch(address);
        else
        {
                if (src.type_regG==INT && dest.type_regG==INT)
                {
                        this->cpu->R_general[dest_num].type_regG=INT;
                        this->cpu->R_general[dest_num].int_valRegG= dest.int_valRegG * src.int_valRegG;
                }
                else 
                {
                        this->cpu->R_general[dest_num].type_regG=FLOAT;
                        if (src.type_regG==INT && dest.type_regG== FLOAT) this->cpu->R_general[dest_num].float_valRegG= src.int_valRegG * dest.float_valRegG;
                        else if (src.type_regG==FLOAT && dest.type_regG== INT) this->cpu->R_general[dest_num].float_valRegG= src.float_valRegG * dest.int_valRegG;
                        else if (src.type_regG==FLOAT && dest.type_regG== FLOAT) this->cpu->R_general[dest_num].float_valRegG= src.float_valRegG * dest.float_valRegG;                        
                }
                
        }

}
void div(string *splited,int address)
{
        //Mul dest, src: dest = dest * src
        RegG dest,src;
        int dest_num=stoi(splited[1].substr(1))-1;
        exchangeDest(splited[1],dest); // doi ra gia tri cho dest
        exChangeSrc(splited[2],src);   // doi ra gia tri cho src
        // if Src la thanh ghi
        if (src.type_regG==REG) 
        {
                exchangeDest(splited[2],src);
        }
        if ((src.type_regG!= INT && src.type_regG!=FLOAT) || (dest.type_regG!= INT && dest.type_regG!=FLOAT)) throw TypeMismatch(address);
        else
        {
                if (src.type_regG==INT && dest.type_regG==INT)
                {
                        if (src.int_valRegG==0) throw DivideByZero(address);
                        else{
                                this->cpu->R_general[dest_num].type_regG=INT;
                                this->cpu->R_general[dest_num].int_valRegG= dest.int_valRegG / src.int_valRegG;
                        }
                        
                }
                else 
                {

                        if (src.type_regG==INT && dest.type_regG== FLOAT)
                        {
                                if (src.int_valRegG==0) throw DivideByZero(address);
                                else this->cpu->R_general[dest_num].float_valRegG= dest.float_valRegG / src.int_valRegG  ;
                        }
                         
                        else if (src.type_regG==FLOAT && dest.type_regG== INT) 
                        {
                                if (src.float_valRegG==0) throw DivideByZero(address);
                                else this->cpu->R_general[dest_num].float_valRegG= dest.int_valRegG /src.float_valRegG;
                        }
                        
                        else if (src.type_regG==FLOAT && dest.type_regG== FLOAT)
                        {
                                if (src.float_valRegG==0) throw DivideByZero(address);
                                else this->cpu->R_general[dest_num].float_valRegG= dest.float_valRegG /src.float_valRegG;
                        } 
                        this->cpu->R_general[dest_num].type_regG=FLOAT;                        
                }
                
        }

}
        // exeComparison
void CmpEQ(string *splited,int address)
{
        // CmpEQ dest, src: if (dest == src) dest = true else dest = false
        RegG dest,src;
        int dest_num=stoi(splited[1].substr(1))-1;
        exchangeDest(splited[1],dest); // doi ra gia tri cho dest
        exChangeSrc(splited[2],src);   // doi ra gia tri cho src
        // if Src la thanh ghi
        if (src.type_regG==REG) 
        {
                exchangeDest(splited[2],src);
        }
        //cout<< src.type_regG << " " << src.int_valRegG;
        //cout<< "\n"<<dest.type_regG << " " << dest.int_valRegG;
        //cout<< "cmp";
        if (src.type_regG==BOOL && dest.type_regG==BOOL)
        {
                if (dest.bool_valRegG==src.bool_valRegG) this->cpu->R_general[dest_num].bool_valRegG= true;
                else this->cpu->R_general[dest_num].bool_valRegG= false;
                this->cpu->R_general[dest_num].type_regG= BOOL;
        }
        else if ((src.type_regG==INT || src.type_regG==FLOAT) && (dest.type_regG==INT || dest.type_regG==FLOAT) )
        {
                float val_Src,val_dest;
                if (src.type_regG==INT) val_Src=src.int_valRegG;
                else val_Src=src.float_valRegG;
                if (dest.type_regG==INT) val_dest= dest.int_valRegG;
                else val_dest= dest.float_valRegG;
        //        cout<< "\n" << val_dest << " " << val_Src;
                if (val_dest== val_Src) this->cpu->R_general[dest_num].bool_valRegG= true;
                else this->cpu->R_general[dest_num].bool_valRegG= false;
                this->cpu->R_general[dest_num].type_regG= BOOL;
        //       cout<< "\n" << this->cpu->R_general[dest_num].bool_valRegG;    
        }
        else throw TypeMismatch(address);


}
void CmpNE(string *splited,int address)
{
        // Add dest, src: dest = dest + src
        RegG dest,src;
        int dest_num=stoi(splited[1].substr(1))-1;
        exchangeDest(splited[1],dest); // doi ra gia tri cho dest
        exChangeSrc(splited[2],src);   // doi ra gia tri cho src
        // if Src la thanh ghi
        if (src.type_regG==REG) 
        {
                exchangeDest(splited[2],src);
        }
        if (src.type_regG==BOOL && dest.type_regG==BOOL)
        {
                if (dest.bool_valRegG!=src.bool_valRegG) this->cpu->R_general[dest_num].bool_valRegG= true;
                else this->cpu->R_general[dest_num].bool_valRegG= false;
                this->cpu->R_general[dest_num].type_regG= BOOL;
        }
        else if ((src.type_regG==INT || src.type_regG==FLOAT) && (dest.type_regG==INT || dest.type_regG==FLOAT) )
        {
                float val_Src,val_dest;
                if (src.type_regG==INT) val_Src=src.int_valRegG;
                else val_Src=src.float_valRegG;
                if (dest.type_regG==INT) val_dest= dest.int_valRegG;
                else val_dest= dest.float_valRegG;

                if (val_dest!= val_Src) this->cpu->R_general[dest_num].bool_valRegG= true;
                else this->cpu->R_general[dest_num].bool_valRegG= false;
                this->cpu->R_general[dest_num].type_regG= BOOL;     
        }
        else throw TypeMismatch(address);
}
void CmpLT(string *splited,int address)
{
        // Add dest, src: dest = dest + src
        RegG dest,src;
        int dest_num=stoi(splited[1].substr(1))-1;
        exchangeDest(splited[1],dest); // doi ra gia tri cho dest
        exChangeSrc(splited[2],src);   // doi ra gia tri cho src
        // if Src la thanh ghi
        if (src.type_regG==REG) 
        {
                exchangeDest(splited[2],src);
        }
        if (src.type_regG==BOOL && dest.type_regG==BOOL)
        {
                if (dest.bool_valRegG<src.bool_valRegG) this->cpu->R_general[dest_num].bool_valRegG= true;
                else this->cpu->R_general[dest_num].bool_valRegG= false;
                this->cpu->R_general[dest_num].type_regG= BOOL;
        }
        else if ((src.type_regG==INT || src.type_regG==FLOAT) && (dest.type_regG==INT || dest.type_regG==FLOAT) )
        {
                float val_Src,val_dest;
                if (src.type_regG==INT) val_Src=src.int_valRegG;
                else val_Src=src.float_valRegG;
                if (dest.type_regG==INT) val_dest= dest.int_valRegG;
                else val_dest= dest.float_valRegG;

                if (val_dest < val_Src) this->cpu->R_general[dest_num].bool_valRegG= true;
                else this->cpu->R_general[dest_num].bool_valRegG= false;
                this->cpu->R_general[dest_num].type_regG= BOOL;     
        }
        else throw TypeMismatch(address);
}
void CmpLE(string *splited,int address)
{
        // Add dest, src: dest = dest + src
        RegG dest,src;
        int dest_num=stoi(splited[1].substr(1))-1;
        exchangeDest(splited[1],dest); // doi ra gia tri cho dest
        exChangeSrc(splited[2],src);   // doi ra gia tri cho src
        // if Src la thanh ghi
        if (src.type_regG==REG) 
        {
                exchangeDest(splited[2],src);
        }
        if (src.type_regG==BOOL && dest.type_regG==BOOL)
        {
                if (dest.bool_valRegG<=src.bool_valRegG) this->cpu->R_general[dest_num].bool_valRegG= true;
                else this->cpu->R_general[dest_num].bool_valRegG= false;
                this->cpu->R_general[dest_num].type_regG= BOOL;
        }
        else if ((src.type_regG==INT || src.type_regG==FLOAT) && (dest.type_regG==INT || dest.type_regG==FLOAT) )
        {
                float val_Src,val_dest;
                if (src.type_regG==INT) val_Src=src.int_valRegG;
                else val_Src=src.float_valRegG;
                if (dest.type_regG==INT) val_dest= dest.int_valRegG;
                else val_dest= dest.float_valRegG;

                if (val_dest <= val_Src) this->cpu->R_general[dest_num].bool_valRegG= true;
                else this->cpu->R_general[dest_num].bool_valRegG= false;
                this->cpu->R_general[dest_num].type_regG= BOOL;     
        }
        else throw TypeMismatch(address);
}
void CmpGT(string *splited,int address)
{
        // Add dest, src: dest = dest + src
        RegG dest,src;
        int dest_num=stoi(splited[1].substr(1))-1;
        exchangeDest(splited[1],dest); // doi ra gia tri cho dest
        exChangeSrc(splited[2],src);   // doi ra gia tri cho src
        // if Src la thanh ghi
        if (src.type_regG==REG) 
        {
                exchangeDest(splited[2],src);
        }
        if (src.type_regG==BOOL && dest.type_regG==BOOL)
        {
                if (dest.bool_valRegG>src.bool_valRegG) this->cpu->R_general[dest_num].bool_valRegG= true;
                else this->cpu->R_general[dest_num].bool_valRegG= false;
                this->cpu->R_general[dest_num].type_regG= BOOL;
        }
        else if ((src.type_regG==INT || src.type_regG==FLOAT) && (dest.type_regG==INT || dest.type_regG==FLOAT) )
        {
                float val_Src,val_dest;
                if (src.type_regG==INT) val_Src=src.int_valRegG;
                else val_Src=src.float_valRegG;
                if (dest.type_regG==INT) val_dest= dest.int_valRegG;
                else val_dest= dest.float_valRegG;

                if (val_dest > val_Src) this->cpu->R_general[dest_num].bool_valRegG= true;
                else this->cpu->R_general[dest_num].bool_valRegG= false;
                this->cpu->R_general[dest_num].type_regG= BOOL;     
        }
        else throw TypeMismatch(address);
}
void CmpGE(string *splited,int address)
{
        // Add dest, src: dest = dest + src
        RegG dest,src;
        int dest_num=stoi(splited[1].substr(1));
        exchangeDest(splited[1],dest); // doi ra gia tri cho dest
        exChangeSrc(splited[2],src);   // doi ra gia tri cho src
        // if Src la thanh ghi
        if (src.type_regG==REG) 
        {
                exchangeDest(splited[2],src);
        }
        if (src.type_regG==BOOL && dest.type_regG==BOOL)
        {
                if (dest.bool_valRegG>=src.bool_valRegG) this->cpu->R_general[dest_num].bool_valRegG= true;
                else this->cpu->R_general[dest_num].bool_valRegG= false;
                this->cpu->R_general[dest_num].type_regG= BOOL;
        }
        else if ((src.type_regG==INT || src.type_regG==FLOAT) && (dest.type_regG==INT || dest.type_regG==FLOAT) )
        {
                float val_Src,val_dest;
                if (src.type_regG==INT) val_Src=src.int_valRegG;
                else val_Src=src.float_valRegG;
                if (dest.type_regG==INT) val_dest= dest.int_valRegG;
                else val_dest= dest.float_valRegG;

                if (val_dest >= val_Src) this->cpu->R_general[dest_num].bool_valRegG= true;
                else this->cpu->R_general[dest_num].bool_valRegG= false;
                this->cpu->R_general[dest_num].type_regG= BOOL;     
        }
        else throw TypeMismatch(address);
}
        //exeLogic
void Not(string *splited,int address)
{
        // Not dest: dest = !dest
        RegG dest;
        int dest_num=stoi(splited[1].substr(1))-1;
        exchangeDest(splited[1],dest); // doi ra gia tri cho dest
        if (dest.type_regG == BOOL)
        {
                this->cpu->R_general[dest_num].bool_valRegG= !dest.bool_valRegG;
        }
        else throw TypeMismatch(address);

}
void And(string *splited,int address)
{
        // And dest, src: dest = dest && src

        RegG dest,src;
        int dest_num=stoi(splited[1].substr(1))-1;
        exchangeDest(splited[1],dest); // doi ra gia tri cho dest
        exChangeSrc(splited[2],src);   // doi ra gia tri cho src
        // if Src la thanh ghi
        if (src.type_regG==REG) 
        {
                exchangeDest(splited[2],src);
        }
        if (dest.type_regG!=BOOL || src.type_regG!=BOOL) throw TypeMismatch(address);
        else
        {
                this->cpu->R_general[dest_num].bool_valRegG= dest.bool_valRegG && src.bool_valRegG;
        }

}
void Or(string *splited,int address)
{
        // Or dest, src: dest = dest || src

        RegG dest,src;
        int dest_num=stoi(splited[1].substr(1))-1;
        exchangeDest(splited[1],dest); // doi ra gia tri cho dest
        exChangeSrc(splited[2],src);   // doi ra gia tri cho src
        // if Src la thanh ghi
        if (src.type_regG==REG) 
        {
                exchangeDest(splited[2],src);
        }
        if (dest.type_regG!=BOOL || src.type_regG!=BOOL) throw TypeMismatch(address);
        else
        {
                this->cpu->R_general[dest_num].bool_valRegG= dest.bool_valRegG || src.bool_valRegG;
        }

}
        //LoadStore
void Move(string *splited,int address)
{
      //  cout<< "dang o Move"<<"\n";
        // Move dest, src: dest = src

        RegG dest,src;
        int dest_num=stoi(splited[1].substr(1))-1;
//        exchangeDest(splited[1],dest); // doi ra gia tri cho dest
        exChangeSrc(splited[2],src);   // doi ra gia tri cho src
        // if Src la thanh ghi
        if (src.type_regG==REG) 
        {
                exchangeDest(splited[2],src);
        }
    //    cout<<src.type_regG<< " " << src.address_valRegG<< "\n";
        this->cpu->R_general[dest_num].type_regG=src.type_regG;
        if (src.type_regG==INT) this->cpu->R_general[dest_num].int_valRegG=src.int_valRegG;
        else if (src.type_regG==FLOAT) this->cpu->R_general[dest_num].float_valRegG=src.float_valRegG;
        else if (src.type_regG==BOOL) this->cpu->R_general[dest_num].bool_valRegG=src.bool_valRegG;
        else if (src.type_regG==A) this->cpu->R_general[dest_num].address_valRegG=src.address_valRegG;
    //    cout<<this->cpu->R_general[dest_num].address_valRegG<< " " << this->cpu->R_general[dest_num].type_regG<< "\n";
}
void Load(string *splited,int address)
{
        // Load dest, src: dest = *src

        RegG dest,src;
        int dest_num=stoi(splited[1].substr(1))-1;
//        exchangeDest(splited[1],dest); // doi ra gia tri cho dest
        exChangeSrc(splited[2],src);   // doi ra gia tri cho src
        // if Src la thanh ghi
        if (src.type_regG==REG) 
        {
                exchangeDest(splited[2],src);
        }
/*        cout<< "\nload\n";
        cout<< src.type_regG << " " << src.address_valRegG;
        cout<< dest_num << endl;*/
        

        if (src.type_regG== A) 
        {       
                if (src.address_valRegG < 0 || src.address_valRegG>65535) throw InvalidOperand(address);
                else
                {
                //        cout<< this->staticM->staticMemmory[src.address_valRegG].type_staticM << " " << this->staticM->staticMemmory[src.address_valRegG].int_valStaticM<<endl;
                        this->cpu->R_general[dest_num].type_regG= this->staticM->staticMemmory[src.address_valRegG].type_staticM;
                        if (this->staticM->staticMemmory[src.address_valRegG].type_staticM==INT) this->cpu->R_general[dest_num].int_valRegG= this->staticM->staticMemmory[src.address_valRegG].int_valStaticM;
                        else if (this->staticM->staticMemmory[src.address_valRegG].type_staticM==FLOAT) this->cpu->R_general[dest_num].float_valRegG= this->staticM->staticMemmory[src.address_valRegG].floatStaticM;
                        else if (this->staticM->staticMemmory[src.address_valRegG].type_staticM==BOOL) this->cpu->R_general[dest_num].bool_valRegG= this->staticM->staticMemmory[src.address_valRegG].boolStaticM;
                }
        }
        else throw TypeMismatch(address);
}
void Store(string *splited,int address)
{
        // Store dest, src: *dest = src

        RegG dest,src;
        int dest_num=stoi(splited[1].substr(1))-1;
        exchangeDest(splited[1],dest); // doi ra gia tri cho dest
        exChangeSrc(splited[2],src);   // doi ra gia tri cho src
        // if Src la thanh ghi
        if (src.type_regG==REG) 
        {
                exchangeDest(splited[2],src);
        }
//        cout<< dest.type_regG << " " << dest.address_valRegG<< endl;
//        cout<< src.type_regG << " " << src.int_valRegG<< endl;
//        cout<< "store";
        if (dest.type_regG==A)
        {
                this->staticM->staticMemmory[dest.address_valRegG].type_staticM= src.type_regG;
                if (src.type_regG==INT) this->staticM->staticMemmory[dest.address_valRegG].int_valStaticM=src.int_valRegG;
                else if (src.type_regG==FLOAT) this->staticM->staticMemmory[dest.address_valRegG].floatStaticM=src.float_valRegG;
                else if (src.type_regG==BOOL) this->staticM->staticMemmory[dest.address_valRegG].boolStaticM=src.bool_valRegG;

            //    cout<< this->staticM->staticMemmory[dest.address_valRegG].int_valStaticM;
        }
        else throw TypeMismatch(address);
}
        //exeScontrol
void Jump(string *splited,int address,int i)
{
        // Jump src: IP = src

        RegG src;
        exChangeSrc(splited[1],src);   // doi ra gia tri cho src
        // if Src la thanh ghi
        if (src.type_regG==REG) 
        {
                exchangeDest(splited[2],src);
        }
        if (src.type_regG==A)
        {
                if (src.address_valRegG >0 && src.address_valRegG<i) this->cpu->IP=src.address_valRegG-1;
                else throw InvalidDestination(address);        
        }
        else throw TypeMismatch(address);
}
void JumIf(string *splited,int address,int i)
{
        // JumpIf dest, src: if (dest) IP = src
        RegG dest,src;
        int dest_num=stoi(splited[1].substr(1))-1;
        exchangeDest(splited[1],dest); // doi ra gia tri cho dest
        exChangeSrc(splited[2],src);   // doi ra gia tri cho src
        // if Src la thanh ghi
        if (src.type_regG==REG) 
        {
                exchangeDest(splited[2],src);
        }
//        cout<<dest.type_regG << " "<<dest.bool_valRegG;
//        cout<<src.type_regG << " " << src.address_valRegG;
        if (dest.type_regG==BOOL && src.type_regG==A) 
        {
                if (src.address_valRegG >0 && src.address_valRegG<i) 
                {
                        if (dest.bool_valRegG) this->cpu->IP=src.address_valRegG-1;
                }
                else throw InvalidDestination(address);        
        }
        else throw TypeMismatch(address);

}
void Call(string *splited,int address,int i)
{
        // Call src
        RegG dest,src;
        exChangeSrc(splited[1],src);   // doi ra gia tri cho src
        // if Src la thanh ghi
        if (src.type_regG==REG) 
        {
                exchangeDest(splited[1],src);
        }
        if (src.type_regG==A)
        {
                if (src.address_valRegG >0 && src.address_valRegG<i) 
                {
                        this->stack->push(this->cpu->IP);
                        this->cpu->IP= src.address_valRegG-1;
                }
                else throw InvalidDestination(address);  
                
        }
        else throw TypeMismatch(address);

}
void Return(string *splited,int address)
{
        this->cpu->IP= this->stack->pop()-1;
}
void Halt(int i)
{
        this->cpu->IP= i;
}
        // exeInOut
void Input(string *splited,int address)
{
      //Input dest: cin >> dest
      //RegG dest;
        int dest_num=stoi(splited[1].substr(1))-1;
     // exchangeDest(splited[1],dest); // doi ra gia tri cho dest
        string input;
        getline(cin,input);
        // check input
        //  check cu phap khi src la hang int
                regex e_int("[+-]?[[:d:]]+"); // hang int co dang gi ?? => sua dk e
                if(regex_match(input, e_int)) 
                {
                        if (input[0]=='0'&& input.length()!=1) throw InvalidInput(address); // check hang int
                        else
                        {
                              this->cpu->R_general[dest_num].type_regG= INT;
                              this->cpu->R_general[dest_num].int_valRegG=stoi(input);
                              return;
                        }
                }
                //  check cu phap khi src la hang float
                regex e_float("[+-]?[[:d:]]+[.][[:d:]]+"); // hang float co dang gi ??
                if(regex_match(input, e_float)) 
                {
                      this->cpu->R_general[dest_num].type_regG= FLOAT;
                      this->cpu->R_general[dest_num].float_valRegG=stof(input);
                      return;
                }
                
                //  check cu phap khi src la hang bool
                if (input=="false") 
                {
                      this->cpu->R_general[dest_num].type_regG= BOOL;
                      this->cpu->R_general[dest_num].bool_valRegG= false;
                      return;
                }
                else if (input=="true")
                {
                     this->cpu->R_general[dest_num].type_regG= BOOL;
                     this->cpu->R_general[dest_num].bool_valRegG= true;
                      return;
                }
                throw InvalidInput(address);

}
void Output(string *splited,int address)
{
        // Output src: cout << src
        RegG src;
        exChangeSrc(splited[1],src);   // doi ra gia tri cho src
        // if Src la thanh ghi
        if (src.type_regG==REG) 
        {
                exchangeDest(splited[1],src);
        }
        if (src.type_regG== A) cout<< src.address_valRegG << "A";
        else if (src.type_regG== INT) cout<< src.int_valRegG;
        else if (src.type_regG== FLOAT) cout<< src.float_valRegG;
        else if (src.type_regG==BOOL) 
        {
                if (src.bool_valRegG) cout<< "true";
                else cout << "false";
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