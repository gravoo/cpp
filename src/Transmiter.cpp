#include "../include/Transmiter.h"

Transmiter::Transmiter()
{
    //ctor
}
Transmiter::Transmiter(int nodeCount,int e,int r,Tree &huffmanTree)
{
    this->nodeCount=nodeCount;
    this->e=e;
    this->r=r;
    this->huffmanTree=huffmanTree;
}
void Transmiter::encode(std::string filePath)
{
    std::ifstream f(filePath, std::ios::binary | std::ios::in);
    char c;
    std::string NYT="";
    while (f.get(c))
    {
        if(huffmanTree.updateTree(c))
        {
            std::cout<<huffmanTree.getNytPath();
            toBits(c);
        }
        else
            std::cout<<huffmanTree.getPath();
    }
	f.close();

}
void Transmiter::decode(std::string filePath)
{
    std::ifstream f(filePath, std::ios::binary | std::ios::in);
    std::string bits="";
    char c;
    int i{0};
    bool flag;
    Node *pointer=huffmanTree.getRoot();
    while (flag)
    {

            if(huffmanTree.isExternalNode(pointer))
            {
                if(huffmanTree.isNYT(pointer))
                {
                    while(i<=e)
                    {
                        f.get(c);
                        i++;
                        bits+=c;
                    }
                    pointer=this->upTree(i,bits,c);

                }
                else
                {
                    pointer=this->upTree(i,bits,pointer->getMark());
                }

            }
            else
            {
                if(!(f.get(c)))
                    flag=false;

                pointer=getNode(pointer,c);
            }

    }
	f.close();

}
void Transmiter::toBits(char c)
{
	 for (int i = 7; i >= 0; i--)
        	std::cout<<((c >> i) & 1);
}
Node *Transmiter::getNode(Node *pointer,char c)
{
    if(c=='0')
        pointer=huffmanTree.getLeft(pointer);
    else
        pointer=huffmanTree.getRight(pointer);

    return pointer;

}
Node *Transmiter::upTree(int &i,std::string &bits,char c)
{
    i=0;
    if(!(bits==""))
        c=toChar(bits);
    std::cout<<c;
    huffmanTree.updateTree(c);
    bits="";
    return huffmanTree.getRoot();
}
char Transmiter::toChar(std::string bits)
{
    char _char=0;

    for (short i = 0; i<bits.length(); i++)
    {
        if(bits[i]=='0')
            _char=_char<<1;
        else
        {
            _char=_char<<1;
            _char++;
        }
    }
    return _char;
}
Transmiter::~Transmiter()
{
    //dtor
}
