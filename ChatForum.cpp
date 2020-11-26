#include<iostream>
#include <map>
#include <set>
#include <ctime>
#include <fstream>
using namespace std;

map<string,int> map1;//存储用户名
map<string,int> map2;//存储密码
map<string,int> map3;//存储id
string id;
int judge[5]={-1,-1,0,0,0};
int id_num;
int pow;//储存用户匿名前的权限

map<int,string> id1;//存储id
map<int,string> title1;//存储帖子title
map<int,string> content1;//存储帖子content
map<int,string> time1;//存储帖子time
map<int,set<int> > idpost1;//存储每个用户在板块1发了那些帖子
set<int> idpost1num;//存储板块1中出现的id
int num1;

map<int,string> id2;//存储id
map<int,string> title2;//存储帖子title
map<int,string> content2;//存储帖子content
map<int,string> time2;//存储帖子time
map<int,set<int> > idpost2;//存储板块2发了那些帖子
set<int> idpost2num;//存储板块2中出现的id
int num2;

map<int,set<string> > content3;//存储板块1的评论content
map<int,set<string> > time3;//存储板块1的评论time
set<int>n1;//帮助输出板块1某个帖子下的所有评论content
set<int>n2;//帮助输出板块1某个帖子下的所有评论time


map<int,set<string> > content4;//存储板块2的评论content
map<int,set<string> > time4;//存储板块2的评论time
set<int>n3;//帮助输出板块2某个帖子下的所有评论content
set<int>n4;//帮助输出板块2某个帖子下的所有评论time

ifstream file1;
ofstream file2;

class User
{
    public:
        User();
        void Enter();
        void Message();
        void Logout();
        void Check();

        virtual void Initialize()=0;
        virtual void Ppublish()=0;
    	virtual void Cpublish()=0;
	    virtual void remove_order()=0;
        virtual void Appoint()=0;
    	virtual void Repeal()=0;
     	virtual void change()=0;
        virtual void remove_moderator()=0;
        ~User();
    private:
    	string username;
        string password;

};


class Post
{
	public:
		Post();
		void Pinitialize();
		void Pstore();
		~Post();
		friend istream &operator>>(istream  &input,Post &p)
        {
            input >> p.n1 >> p.n2 >> p.file_id >> p.file_title >> p.file_content >> p.file_t;
            return input;
        }

        friend ostream &operator<<(ostream  &output,Post &p)
        {
            output << p.n1 << " "<< p.n2 << " " << p.file_id << " " << p.file_title << " " << p.file_content << " " << p.file_t << endl;
            return output;
        }
	private:
		int n1;//用于表示文件中帖子是第几个
		int n2;//用于存储文件中发帖者是第几个用户
	    string file_id;//用于读取文件中存的id
	    string file_title;
        string file_content;
        string file_t;
};

class Comment
{
	public:
		Comment();
		void Cinitialize();
		void Cstore();
		~Comment();
		friend istream &operator>>(istream  &input,Comment &c)
        {
            input >> c.n >> c.file_content >> c.file_t;
            return input;
        }
        friend ostream &operator<<(ostream  &output,Comment &c)
        {
            output << c.n << " " << c.file_content << " " << c.file_t << endl;
            return output;
        }
	private:
	    int n;//用于表示文件中该评论对应的帖子是第几个
        string file_content;//用于读取文件中存的评论内容
        string file_t;//用于读取文件中存的评论时间
};

class orderUser:public User
{
	public:
		orderUser();
		void Ppublish();
	    void Cpublish();
		void remove_order();
		void change();

		void Initialize();
		void Appoint();
	    void Repeal();
        void remove_moderator();
		~orderUser();
		friend istream &operator>>(istream  &input,orderUser &o)
        {
            input >> o.username>> o.password >> o.file_id;
            return input;
        }
	private:
	    string title;
        string content;
        string t;
    	string username;
        string password;
		string file_id;
};

class Admin:public User
{
	public:
		Admin();
		void Initialize();
		void Ppublish();
	    void Cpublish();
	    void remove_order();
	    void change();
		void remove_moderator();

		void Appoint();
		void Repeal();
		~Admin();
		friend istream &operator>>(istream  &input,Admin &a)
        {
            input >> a.username>> a.password >> a.file_id;
            return input;
        }
	private:
    	string username;
        string password;
		string file_id;
};

class Anonymity:public User
{
	public:
		Anonymity();
		void Initialize();
		void Ppublish();
	    void Cpublish();
	    void remove_order();
		void remove_moderator();
		void Appoint();
		void Repeal();

		void change();
		~Anonymity();
};


class Moderator:public orderUser
{
	public:
		Moderator();
		void remove_moderator();
		~Moderator();
};

User::User()
{

}

void User::Enter()
{
   cout<<"请输入你的用户名：";
    cin>>username;
    cout<<"请输入你的密码：";
    cin>>password;
    int j=0;
    map<string,int>::iterator iter1=map1.begin();
    map<string,int>::iterator iter2=map2.begin();
    map<string,int>::iterator iter3=map3.begin();
    iter1=map1.find(username);
    iter2=map2.find(password);
    if(iter1->second==iter2->second&&iter1->second!=0&&iter2->second!=0)
    {
    	id_num=iter1->second;
        j=1;
	}
    if(j==1)
    {
    	for(int i=0;iter3!=map3.end()&&i!=1;iter3++)
		{
			if(iter3->second==iter1->second)
			{
				id=iter3->first;
				i=1;
		    }

		}
        cout<<id<<",欢迎登录"<<endl;
    }
    else
    {
    	cout<<"用户名或密码错误"<<endl;
    	Enter();
	}
}


void User::Logout()
{
	cout<<"注销成功"<<endl;
	cout<<"请输入你的用户名：";
    cin>>username;
    cout<<"请输入你的密码：";
    cin>>password;
    int j=0;
    map<string,int>::iterator iter1=map1.begin();
    map<string,int>::iterator iter2=map2.begin();
    map<string,int>::iterator iter3=map3.begin();
    iter1=map1.find(username);
    iter2=map2.find(password);
    if(iter1->second==iter2->second&&iter1->second!=0&&iter2->second!=0)
    {
    	id_num=iter1->second;
        j=1;
	}
    if(j==1)
    {
    	for(int i=0;iter3!=map3.end()&&i!=1;iter3++)
		{
			if(iter3->second==iter1->second)
			{
				id=iter3->first;
				i=1;
		    }

		}
        cout<<id<<",欢迎登录"<<endl;
    }
    else
    {
    	cout<<"用户名或密码错误"<<endl;
    	Enter();
	}
}

void User::Message()
{
	cout<<"用户基本信息:"<<endl;
	cout<<"id:"<<id<<"      ";
	if(judge[id_num-1]==0)
	    cout<<"权限:普通用户";
	else if(judge[id_num-1]==-1)
	    cout<<"权限:管理员";
	else
		cout<<"权限:版主";
	cout<<endl;
	cout<<"用户名:"<<username;
	cout<<"      密码:"<<password<<endl;
}

void User::Check()
{
	int section;
	cout<<"你想查看哪个板块的帖子:";
	cin>>section;

	map<int,string>::iterator iter;
	set<int>::iterator iter1;
	set<string>::iterator iter2;
	set<int>::iterator iter3;
	set<string>::iterator iter4;
    if(section==1)
	{
		int num=1;
		while(num<num1)
		{

			iter=id1.find(num);
			if(iter!=id1.end())
			{
				cout<<"帖子"<<num<<":";
			    cout<<"用户名:"<<iter->second;
			    cout<<"      ";
			    iter=title1.find(num);
			    cout<<"标题:"<<iter->second;
			    cout<<endl;
			    iter=content1.find(num);
			    cout<<"      内容:"<<iter->second;
			    cout<<endl;
			    iter=time1.find(num);
			    cout<<"      时间:"<<iter->second;
			    cout<<endl;
			}


			iter1=n1.find(num);
			iter2=content3[*iter1].begin();
			iter3=n2.find(num);
			iter4=time3[*iter3].begin();
			int n_=1; //表示该评论是第几个
			while(iter2!=content3[*iter1].end()&&*iter1==num)
			{
				cout<<"评论"<<n_<<":";
			    cout<<"内容:"<<*iter2;
			    cout<<endl;
			    cout<<"      时间:"<<*iter4;
			    cout<<endl;
			    iter2++;
			    iter4++;
			    n_++;
			}
			num++;
		}
	}
	else
	{
		int num=1;
		while(num<num2)
		{
			iter=id2.find(num);
			if(iter!=id2.end())
			{
				cout<<"帖子"<<num<<":";
			    cout<<"用户名:"<<iter->second;
			    cout<<"      ";
			    iter=title2.find(num);
			    cout<<"标题:"<<iter->second;
			    cout<<endl;
			    iter=content2.find(num);
			    cout<<"      内容:"<<iter->second;
			    cout<<endl;
			    iter=time2.find(num);
			    cout<<"      时间:"<<iter->second;
			    cout<<endl;
			}


			iter1=n3.find(num);
			iter2=content4[*iter1].begin();
			iter3=n4.find(num);
			iter4=time4[*iter3].begin();
			int n_=1;//表示该评论是第几个
			while(iter2!=content4[*iter1].end()&&*iter1==num)
			{
			    cout<<"评论"<<n_<<":";
			    cout<<"内容:"<<*iter2;
			    cout<<endl;
			    cout<<"      时间:"<<*iter4;
			    cout<<endl;
			    iter2++;
			    iter4++;
			    n_++;
			}
			num++;
		}
	}
}

User::~User()
{

}

Post::Post()
{

}

void Post::Pinitialize()
{
    Post p;
    string e="文件不存在";
	file1.open("板块1帖子.txt");
	try
	{
     if(!file1)
        throw e;
    }
    catch (string &error)
    {
        cout <<error<< endl;
    }
	while(file1>>p)
	{
		id1.insert({p.n1,p.file_id});
  	    title1.insert({p.n1,p.file_title});
    	content1.insert({p.n1,p.file_content });
    	time1.insert({p.n1,p.file_t });
    	idpost1[p.n2].insert(p.n1);
		idpost1num.insert(p.n2);
	}
	num1=p.n1+1;
	file1.close();

	file1.open("板块2帖子.txt");
	try
	{
     if(!file1)
        throw e;
    }
    catch (string &error)
    {
        cout <<error<< endl;
    }
	while(file1>>p)
	{
		id2.insert({p.n1,p.file_id});
  	    title2.insert({p.n1,p.file_title});
    	content2.insert({p.n1,p.file_content });
    	time2.insert({p.n1,p.file_t });
    	idpost2[p.n2].insert(p.n1);
		idpost2num.insert(p.n2);
	}
	num2=p.n1+1;
	file1.close();
}

void Post::Pstore()
{
	Post p;
	int num=1;
	file2.open("板块1帖子.txt");
	map<int,string>::iterator iter;
	map<string,int>::iterator it;
	while(num<num1)
	{
		iter=id1.find(num);
		if(iter!=id1.end())
		{
			string s=iter->second;
			p.n1=num;
			it=map3.find(s);
			p.n2=it->second;
			p.file_id=iter->second;
			iter=title1.find(num);
			p.file_title=iter->second;
			iter=content1.find(num);
			p.file_content=iter->second;
			iter=time1.find(num);
			p.file_t=iter->second;
			file2<<p;
		}
		num++;
	}
	file2.close();
	file2.open("板块2帖子.txt");
	num=1;
	while(num<num2)
	{
		iter=id2.find(num);
		if(iter!=id2.end())
		{
			string s=iter->second;
			p.n1=num;
			it=map3.find(s);
			p.n2=it->second;
			p.file_id=iter->second;
			iter=title2.find(num);
			p.file_title=iter->second;
			iter=content2.find(num);
			p.file_content=iter->second;
			iter=time2.find(num);
			p.file_t=iter->second;
			file2<<p;
		}
		num++;
	}
	file2.close();
}

Post::~Post()
{

}

Comment::Comment()
{

}

void Comment::Cinitialize()
{

    Comment c;
	file1.open("板块1评论.txt");
	while(file1>>c)
	{
		content3[c.n].insert(c.file_content);
        time3[c.n].insert(c.file_t);

	    content3[c.n].insert(c.file_content);
        time3[c.n].insert(c.file_content);
        n1.insert(c.n);
        n2.insert(c.n);
	}
	file1.close();

	file1.open("板块2评论.txt");
	while(file1>>c)
	{
		content4[c.n].insert(c.file_content);
        time4[c.n].insert(c.file_t);
        n3.insert(c.n);
        n4.insert(c.n);
	}
	file1.close();

}

void Comment::Cstore()
{
	Comment c;
	file2.open("板块1评论.txt");
	set<int>::iterator iter1;
	set<string>::iterator iter2;
	set<int>::iterator iter3;
	set<string>::iterator iter4;
	int num=1;
	while(num<num1)
	{
		iter1=n1.find(num);
		iter2=content3[*iter1].begin();
		iter3=n2.find(num);
		iter4=time3[*iter3].begin();
		int n_=1;//表示该评论是第几个
		while(iter2!=content3[*iter1].end()&&*iter1==num)
		{
			c.n=num;
			c.file_content=*iter2;
			c.file_t=*iter4;
			file2<<c;
			iter2++;
			iter4++;
			n_++;
		}
		num++;
	}
	file2.close();
	file2.open("板块2评论.txt");
	num=1;
	while(num<num2)
	{
		iter1=n3.find(num);
		iter2=content4[*iter1].begin();
		iter3=n4.find(num);
		iter4=time4[*iter3].begin();
		int n_=1;//表示该评论是第几个
		while(iter2!=content4[*iter1].end()&&*iter1==num)
		{
			c.n=num;
			c.file_content=*iter2;
			c.file_t=*iter4;
			file2<<c;
			iter2++;
			iter4++;
			n_++;
		}
		num++;
	}
	file2.close();
}

Comment::~Comment()
{

}

orderUser::orderUser()
{

}

void orderUser::Initialize()
{
	orderUser o;
    string e="文件不存在";
	file1.open("普通用户信息.txt");
	try
	{
     if(!file1)
        throw e;
    }
    catch (string &error)
    {
        cout <<error<< endl;
    }
    int num=3;
	while(file1>>o)
	{
	    map1.insert({o.username,num});
        map2.insert({o.password,num});
        map3.insert({o.file_id,num});
        num++;
    }
    file1.close();
}

void orderUser::Ppublish()
{
	int section;
	cout<<"你想在哪个板块发表帖子:";
	cin>>section;
	cout<<"请输入你的标题:";
	cin>>title;
	cout<<"请输入你的帖子内容:";
	cin>>content;

	time_t now_time= time(NULL);
    char tmp[64];
    strftime( tmp, sizeof(tmp), "%Y/%m/%d-%X",localtime(&now_time) );
    t=tmp;

	if(section==1)
	{
		cout<<"发帖成功"<<endl;
		id1.insert({num1,id});
        title1.insert({num1,title});
        content1.insert({num1,content});
        time1.insert({num1,t});
        idpost1[id_num].insert(num1);

        set<int>::iterator it;
		it=idpost1num.find(id_num);
        if(*it!=id_num)
        {
        	idpost1num.insert(id_num);
		}

        num1++;
	}
	else
	{
		cout<<"发帖成功"<<endl;
		id2.insert({num2,id});
        title2.insert({num2,title});
        content2.insert({num2,content});
        time2.insert({num2,t});
        idpost2[id_num].insert(num2);

        set<int>::iterator it;
		it=idpost2num.find(id_num);
        if(*it!=id_num)
        {
        	idpost2num.insert(id_num);
		}

        num2++;
	}

}

void orderUser::Cpublish()
{
	int section;
    cout<<"你想对哪个板块的帖子发表评论：";
	cin>>section;
	int num;
	cout<<"你想对哪个帖子发表评论：";
	cin>>num;
	cout<<"请输入你的评论内容：";
	cin>>content;
	time_t now_time= time(NULL);;
    char tmp[64];
    strftime( tmp, sizeof(tmp), "%Y/%m/%d-%X",localtime(&now_time) );
    t=tmp;

	if(section==1)
	{
		cout<<"评论成功"<<endl;
        content3[num].insert(content);
        time3[num].insert(t);
        n1.insert(num);
        n2.insert(num);

	}
	else
	{
		cout<<"评论成功"<<endl;
		content4[num].insert(content);
        time4[num].insert(t);
        n3.insert(num);
        n4.insert(num);

	}

}

void orderUser::remove_order()
{
	int j=0;//用于判断这个帖子的id是否为自己
	int section;
	cout<<"你想删除哪个板块的帖子:";
	cin>>section;
	int num;
	cout<<"你想删除哪个帖子:";
	cin>>num;

	set<int>::iterator it;
	set<int>::iterator it1;
	map<int,string>::iterator iter;
	set<int>::iterator iter1;
	if(section==1)
	{
		it=idpost1num.find(id_num);
	    it1=idpost1[*it].begin();

	    for(;*it==id_num&&it1!=idpost1[*it].end()&&j!=1;it1++)
	    {
	    	if(*it1==num)
	        {
	        	iter1=n1.find(num);
	        	if(iter1==n1.end())
	        	    j=1;
			}
		}
	}
	else
	{
		it=idpost2num.find(id_num);
	    it1=idpost2[*it].begin();
	    for(;*it==id_num&&it1!=idpost2[*it].end()&&j!=1;it1++)
	    {
	    	if(*it1==num)
	        {
	        	iter1=n3.find(num);
	        	if(iter1==n3.end())
	        	    j=1;
			}
		}

	}


	if(section==1&&j==1)
	{
		cout<<"删除成功"<<endl;
		iter=id1.find(num);
		id1.erase(iter);
		iter=title1.find(num);
		title1.erase(iter);
		iter=content1.find(num);
		content1.erase(iter);
		iter=time1.find(num);
		time1.erase(iter);

	}
	else if(section==2&&j==1)
	{
		cout<<"删除成功"<<endl;
		iter=id2.find(num);
		id2.erase(iter);
		iter=title2.find(num);
		title2.erase(iter);
		iter=content2.find(num);
		content2.erase(iter);
		iter=time2.find(num);
		time2.erase(iter);

	}
	else
	{
		cout<<"你无权限删除该帖"<<endl;
	}
}

void orderUser::Appoint()
{

}

void orderUser::Repeal()
{

}

void orderUser::change()
{

}


void orderUser::remove_moderator()
{

}

orderUser::~orderUser()
{

}

Admin::Admin()
{

}

void Admin::Initialize()
{
	Admin a;
    string e="文件不存在";
	file1.open("管理员信息.txt");
	try
	{
     if(!file1)
        throw e;
    }
    catch (string &error)
    {
        cout <<error<< endl;
    }
    int num=1;
	while(file1>>a)
	{
	    map1.insert({a.username,num});
        map2.insert({a.password,num});
        map3.insert({a.file_id,num});
        num++;
    }
    file1.close();
}

void Admin::Ppublish()
{

}

void Admin::Cpublish()
{

}

void Admin::remove_order()
{

}

void Admin::Appoint()
{
	int i;
	int j;
	cout<<"你要任命第几个组员为版主:";
	cin>>i;
	cout<<"你要任命这个组员为第几个版主:";
	cin>>j;
	int k=0;
	while(k<5&&judge[k]!=j&&j!=0&&j!=-1)
	{
		k++;
	}

	if(k==5)
	{


		if(j==1||j==2)
 		{
			cout<<"任命成功"<<endl;
			judge[i+1]=j;
		}
		else
		{
			cout<<"不存在这个版块"<<endl;
		}
	}
	else
	    cout<<"已存在此版主，无法进行重复任命"<<endl;
}

void Admin::Repeal()
{
	int section;
	cout<<"你要撤销第几个版主:";
	cin>>section;
	if(section==1||section==2)
 	{
 		 int k=0;
		 while(k<5&&judge[k]!=section&&section!=0&&section!=-1)
	    {
		    k++;
	    }
	    if(k==5)
	    {
	    	cout<<"不存在此版主"<<endl;
		}
		else
		{
			judge[k]=0;
			cout<<"撤销成功"<<endl;
		}
	}
	else
	{
		cout<<"不存在这个版块"<<endl;
	}
}

void Admin::change()
{

}

void Admin::remove_moderator()
{

}

Admin::~Admin()
{

}

void Anonymity::Initialize()
{

}

Anonymity::Anonymity()
{

}

void Anonymity::Ppublish()
{

}

void Anonymity::Cpublish()
{

}

void Anonymity::remove_order()
{

}

void Anonymity::Appoint()
{

}

void Anonymity::Repeal()
{

}

void Anonymity::change()
{
	judge[id_num-1]=-2;
}

void Anonymity::remove_moderator()
{

}

Anonymity::~Anonymity()
{

}

Moderator::Moderator()
{

}

void Moderator::remove_moderator()
{
	int num;
	cout<<"你想删除哪个帖子:";
	cin>>num;
	map<int,string>::iterator iter;
	set<int>::iterator iter1;
	set<int>::iterator iter2;
	if(judge[id_num-1]==1)
	{
		cout<<"删除成功"<<endl;
		iter=id1.find(num);
		id1.erase(iter);
		iter=title1.find(num);
		title1.erase(iter);
		iter=content1.find(num);
		content1.erase(iter);
		iter=time1.find(num);
		time1.erase(iter);

		iter1=n1.find(num);
		n1.erase(iter1);
		iter2=n2.find(num);
		n2.erase(iter2);
	}
	else if(judge[id_num-1]==2)
	{
		cout<<"删除成功"<<endl;
		iter=id2.find(num);
		id2.erase(iter);
		iter=title2.find(num);
		title2.erase(iter);
		iter=content2.find(num);
		content2.erase(iter);
		iter=time2.find(num);
		time2.erase(iter);

		iter1=n3.find(num);
		n3.erase(iter1);
		iter2=n4.find(num);
		n4.erase(iter2);
	}
	else
	{
		cout<<"不存在这个版块";
	}
}

Moderator::~Moderator()
{

}

int main()
{
    Post p;
    p.Pinitialize();
    Comment c;
    c.Cinitialize();
	orderUser o;
	Admin a;
	Anonymity ano;
	Moderator m;
	User *u;
	u=&o;
	u->Initialize();
	u=&a;
	u->Initialize();
    u->Enter();
	int operate=7;

    while(operate!=100)
    {

	    if(judge[id_num-1]==0)
	    {
		    u=&o;
		    cout<<"你的权限是普通用户"<<endl;
		    while(operate!=-1&&operate!=-2)
	        {
		        cout<<"你想执行哪一种操作(-2是匿名操作，-1是注销操作，0是查看用户基本信息操作,1是发帖操作，2是评论操作，3是查看操作，4是删帖操作):";
		        cin>>operate;
		        if(operate==-2)
    		    {
    		    	pow=0;
    		    	u=&ano;
	    		    u->change();
		        }

		        else if(operate==0)
    		    {
	    		    u->Message();
		        }
		        else if(operate==1)
    		    {
	    		    u->Ppublish();
	    		    p.Pstore();
			        c.Cstore();
		        }
    		    else if(operate==2)
	    	    {
		    	    u->Cpublish();
		    	    p.Pstore();
			        c.Cstore();
		        }
    		    else if(operate==3)
	    	    {
		    	    u->Check();
		        }
    		    else if(operate==4)
	    	    {
		    	    u->remove_order();
					p.Pstore();
			        c.Cstore();
		        }
		        else if(operate!=-1)
		        {
		        	cout<<"无效操作"<<endl;
				}
	        }
	    }
    	else if(judge[id_num-1]==-1)
	    {
	    	u=&a;
		    cout<<"你的权限是管理员"<<endl;
    		while(operate!=-1&&operate!=-2)
	        {
		        cout<<"你想执行哪一种操作(-2是匿名,-1是注销操作，0是查看用户基本信息操作，1是查看操作，2是任命版主操作，3是撤销版主操作):";
		        cin>>operate;
		        if(operate==-2)
    		    {
    		    	pow=-1;
    		    	u=&ano;
	    		    u->change();
		        }
		        else if(operate==0)
    		    {
	    		    u->Message();
		        }
		        else if(operate==1)
		        {
			        u->Check();
		        }
    		    else if(operate==2)
	    	    {
		    	    u->Appoint();
		        }
		        else if(operate==3)
	    	    {
		    	    u->Repeal();
		        }

    		    else if(operate!=-1)
    		    {
    		    	cout<<"无效操作"<<endl;

		        }
		    }
    	}
    	else if(judge[id_num-1]==-2)
    	{
	    	u=&ano;
		    cout<<"你是匿名用户"<<endl;
    		while(operate!=0)
	        {
		        cout<<"你想执行哪一种操作(0是退出匿名，1是查看操作):";
		        cin>>operate;
				if(operate==0)
		        {
			        judge[id_num-1]=pow;
		        }
		        if(operate==1)
		        {
			        u->Check();
		        }

    		    else if(operate!=0)
    		    {
    		    	cout<<"无效操作"<<endl;

		        }
		    }
    	}
	    else
	    {
	    	u=&m;
		    cout<<"你的权限是版主"<<",你是版主"<<judge[id_num-1]<<endl;
		    while(operate!=-1&&operate!=-2)
	        {
    		    cout<<"你想执行哪一种操作(-2是匿名,-1是注销操作，0是查看用户基本信息操作，1是发帖操作，2是评论操作，3是查看操作，4是删除自己帖操作，5是删除板块帖操作):";
	    	    cin>>operate;
	    	    if(operate==-2)
    		    {
    		    	pow=judge[id_num-1];
    		    	u=&ano;
	    		    u->change();
		        }
	    	    else if(operate==0)
    		    {
	    		    u->Message();
		        }
		        else if(operate==1)
		        {
			        u->Ppublish();
			        p.Pstore();
		         	c.Cstore();
		        }
    		    else if(operate==2)
	    	    {
		    	    u->Cpublish();
		    	    p.Pstore();
			        c.Cstore();
		        }
    		    else if(operate==3)
	    	    {
		    	    u->Check();
		        }
		        else if(operate==4)
    		    {
	    		    u->remove_order();
					p.Pstore();
			        c.Cstore();
		        }

		        else if(operate==5)
    		    {
	    		    u->remove_moderator();
					p.Pstore();
			        c.Cstore();
		        }
		        else if(operate!=-1)
    		    {
    		    	cout<<"无效操作"<<endl;

		        }

	        }
	    }
	    if(operate==-1)
		{
			u->Logout();
		}
        operate=7;
    }

}
