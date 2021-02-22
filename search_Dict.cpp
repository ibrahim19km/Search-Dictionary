#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class article_node;
class article_list;
class author_list_node;
class author_data_node;
class author_data;
class publication_node;
class publication_list;
class array_list;

class array_list
{
	public:
		static const int max_size = 10;
		string array[10];
		int length;
	
	array_list()
	{
		length = 0;
	}

	bool isFull()
	{
		return length == max_size;
	}

	bool isEmpty()
	{
		return length == 0;
	}
	
	void insertEnd(string value)
	{
		if(!isFull())
		{
			array[length++]	= value;
		}
		else
		{
			cout << "Array Is Full." << endl;
		}
	}
	
	void print_list()
	{
		if(!isEmpty())
		{
			cout << endl;
			for (int i = 0; i < length; i++)
			{
				cout << " " << array[i];
			}
		}
		else
		{
			cout << "List Is Empty." << endl;
		}
	}
};

class author_data_node
{
	public:
		string name;
		publication_node *publications;
		author_data_node *next;
};

class article_node
{
	public:
		string title;
		string journal;
		string publisher;
		string year;
		string month;
		author_list_node *al;
		article_node *next;
};

class publication_node
{
	public:
		article_node *data;
		publication_node *next;
};

class author_list_node
{
	public:
		author_data_node *data;
		author_list_node *next;
};

class author_data
{
	public:
		author_data_node *start;
		author_data_node *end;
		author_data_node *loc;
		author_data_node *ploc;
	
	author_data()
	{
		start = NULL;
		end = NULL;
		loc = NULL;
		ploc = NULL;
	}
	
	bool isEmpty()
	{
		return start == NULL;
	}

	author_data_node * Insert_Author(string name)
	{
		author_data_node *nn = new author_data_node();
		nn->name = name;
		
		if (!isEmpty())
		{
			Search_Author(name);
			if(loc != NULL)
			{
				return loc;
			}
			else
			{
				end->next = nn;
				end = nn;
				nn->next = NULL;
				return nn;
			}
		}
		else
		{
			start = nn;
			end = nn;
			nn->next = NULL;
			return nn;
		}
	}
	
	void Publication_List(article_node *a, author_data_node *b)
	{		
		if(b->publications == NULL)
		{
			b->publications = new publication_node();
			b->next = NULL;
			b->publications->data = a;
		}
		else
		{
			publication_node *temp = b->publications;
			while(temp->next != NULL)
			{
				temp = temp->next;
			}
			publication_node *nn = new publication_node();
			nn->data = a;
			temp->next = nn;
			nn->next = NULL;
		}
	}
	 
	bool search_in(string name, article_node *a)
	{
	//	cout << "Search_in Called." << endl;
		author_list_node *temp = new author_list_node();
		temp = a->al;
		bool check = false;
		while(temp != NULL)
		{
		//	cout << "While Called." << endl;
			if(temp->data->name == name)
			{
			//	cout << "If Called." << endl;
				check = true;
			}
			else
			{
			//	cout << "Else Called." << endl;
				check = false;
			}
			temp = temp->next;
		}
		return check;
	}
	
	bool Exist_Author(string name)
	{
    	Search_Author(name);
        if(loc == NULL)
        {
        	return false;
        }
        else
        {
    		return true;
        }
    }
	
	void Print_Author()
	{
		author_data_node *temp = new author_data_node();
		temp = start;
		while(temp != NULL)
		{
			cout << "Author:    " << temp->name << endl;
			publication_node *temp1 = new publication_node();
			temp1 = temp->publications;
//			total_articles(temp->name);
//			publication_per_year(temp->name);
//			number_of_coAuhtor(temp->name);
//			number_of_paper(temp->name);
//			journal_name(temp->name);
			cout << endl;
			while(temp1 != NULL)
			{
				cout << "Title :    " << temp1->data->title << endl;
				cout << "Journal:   " << temp1->data->journal << endl;
				cout << "Publisher: " << temp1->data->publisher << endl;
				cout << "Month:     " << temp1->data->month << endl;
				cout << "Year:      " << temp1->data->year << endl;
				cout << endl;
				temp1 = temp1->next;
			}
			temp = temp->next;
			cout << endl;
		}
	}
	
	author_data_node * Search_Author(string name)
	{	
		if(!isEmpty())
		{	
			loc = start;	
			while(loc != NULL && loc->name != name)
			{					
				loc = loc->next;
			}
			return loc;
		}
		else
		{
			cout << "Author Do Not Exist." << endl;
			return NULL;
		}
	}
	
	// Method 1
	void total_articles(string name)
	{
		author_data_node *mm = Search_Author(name);
		int count;
		count = 0;
		if(mm != NULL)
		{
			publication_node *temp = new publication_node();
			temp = mm->publications;
			while(temp != NULL)
			{
				count++;
				temp = temp->next;
			}
			cout << endl;
			cout << "Total Article(s) Published by " << name << " are: " << count << " Publication(s)." << endl;
		}
		else
		{
			cout << "Name Not Found." << endl;
			return;
		}
	}
	
	// Method 2
	void publication_per_year(string name)
	{
		author_data_node *mm = Search_Author(name);
		int y18 = 0;
		int y19 = 0;
		if(mm != NULL)
		{
			cout << endl;
			cout << "Publication(s) Per Year:" << endl;
			cout << endl;
			publication_node *temp = new publication_node();
			temp = mm->publications;
			while(temp != NULL)
			{
				article_node *aa = new article_node();
				aa = temp->data;
				if(aa->year == "{2018}")
				{		
					y18++;
				}
				else if(aa->year == "{2019}")
				{
					y19++;
				}
				temp = temp->next;	
			}
			cout << "In 2018:      " << y18 << " publication(s)." << endl;
			cout << "In 2019:      " << y19 << " publication(s)." << endl;
		}
		else
		{
			cout << "Name Not Found." << endl;
			return;
		}
	}
	
	// Method 3
	void number_of_coAuhtor(string name)
	{
		author_data_node *mm = Search_Author(name);
		if(mm != NULL)
		{
			cout << endl;
			cout << "Number Of Co_Authors:" << endl;
			cout << endl;
			publication_node *temp = new publication_node();
			temp = mm->publications;
			int publication = 1;
			while(temp != NULL)
			{
				int co_author = 0;
				article_node *aa = new article_node();
				aa = temp->data;
				author_list_node *ad = new author_list_node();
				ad = aa->al;
				while(ad != NULL)
				{
					co_author ++;
					ad = ad->next;
				}
				cout <<"Publication: " << publication << endl << "Year: " << aa->year << endl << "Number of Co_Authors: " << co_author - 1 << endl;
				cout << endl;
				publication ++;
				temp = temp->next;
			}
		}
		else
		{
			cout << "Name Not Found." << endl;
		}
	}
	
	// Method 4
	void number_of_paper(string name)
	{	
		author_data_node *mm = Search_Author(name);
		int p1 = 0;
		int p2 = 0;
		int p3 = 0;
		int p4 = 0;
		int p5 = 0;
		int p6 = 0;
		int p7 = 0;
		int p8 = 0;
		int p9 = 0;
		int p10 = 0;
		if(mm != NULL)
		{
			cout << "Number Of Papers:" << endl;
			cout << endl;
			publication_node *temp = new publication_node();
			temp = mm->publications;
			while(temp != NULL)
			{
				article_node *aa = new article_node();
				aa = temp->data;
				author_list_node *ad = new author_list_node();
				ad = aa->al;
				int iterate = 0;
				while(ad != NULL)
				{	
					iterate ++;
					if(mm->name == ad->data->name)
					{
						break;
					}
					ad = ad->next;
				}
				if(iterate == 1)
				{
					p1 ++;
				}
				else if(iterate == 2)
				{
					p2++;
				}
				else if(iterate == 3)
				{
					p3++;
				}
				else if(iterate == 4)
				{
					p4++;
				}
				else if(iterate == 5)
				{
					p5++;
				}
				else if(iterate == 6)
				{
					p6++;
				}
				else if(iterate == 7)
				{
					p7++;
				}
				else if(iterate == 8)
				{
					p8++;
				}
				else if(iterate == 9)
				{
					p9++;
				}
				else if(iterate == 10)
				{
					p10++;
				}
				temp = temp->next;
			}
			cout << "Position  1  : " << p1 << endl;
			cout << "Position  2  : " << p2 << endl;
			cout << "Position  3  : " << p3 << endl;
			cout << "Position  4  : " << p4 << endl;
			cout << "Position  5  : " << p5 << endl;
			cout << "Position  6  : " << p6 << endl;
			cout << "Position  7  : " << p7 << endl;
			cout << "Position  8  : " << p8 << endl;
			cout << "Position  9  : " << p9 << endl;
			cout << "Position  10 : " << p10 << endl;
		}
		else
		{
			cout << "Name Not Found." << endl;
			return;
		}
	}
	
	// Method 5
	void journal_name(string name)
	{
		author_data_node *mm = Search_Author(name);
		if(mm != NULL)
		{
			cout << endl;
			cout << "Journals Name:" << endl;
			cout << endl;
			publication_node *temp = new publication_node();
			temp = mm->publications;
			while(temp != NULL)
			{
				article_node *aa = new article_node();
				aa = temp->data;													
				author_list_node *ad = new author_list_node();
				ad = aa->al;
				int iterate = 0;
				while(ad != NULL)
				{
					iterate ++;
					if(mm->name == ad->data->name)
					{
						break;
					}
					ad = ad->next;
				}
				cout << "Journal: " << aa->journal << endl << "Position: " << iterate << endl << "Year: " << aa->year << endl;
				temp = temp->next;
			}
		}
		else
		{
			cout << "Name Not Found." << endl;
		}
	}
};

class article_list
{
	public:
		article_node *start;
		article_node *end;
		article_node *loc;
		article_node *ploc;
		
	article_list()
	{
		start = NULL;
		end = NULL;
		loc = NULL;
		ploc = NULL;
	}
	
	bool isEmpty()
	{
		return start == NULL;
	}
	
	article_node * Insert_Article(string title, string journal, string publisher, string year, string month)
	{
		article_node *nn = new article_node();
		nn->title = title;
		nn->journal = journal;
		nn->month = month;
		nn->publisher = publisher;
		nn->year = year;
		if(!isEmpty())
		{
			Search_Article(title);
			if(loc != NULL)
			{
				return loc;
			}
			else
			{
				end->next = nn;
				end = nn;
				return nn;
			}
		}
		else
		{
			start = nn;
			end = nn;
			nn->next = NULL;
			return nn;	
		}
	}
	
	article_node * Search_Article(string title)
	{
		if(!isEmpty())
		{
			loc = start;
			while(loc != NULL && loc->title != title)
			{			
				loc = loc->next;
			}
			return loc;
		}
		else
		{
			cout << "List Is Empty. Can't Search." << endl;
			return NULL;
		}
	}
	
	void Enter_Author_List(author_data_node *a, article_node *b)
	{	
		if(b->al == NULL)
		{	
			b->al = new author_list_node();
			b->next = NULL;
			b->al->data = a;
		}
		else
		{
			author_list_node *temp = b->al;
			while(temp->next != NULL)
			{	
				temp = temp->next;
			}
			author_list_node *nn = new author_list_node();
			nn->data = a;
			temp->next = nn;
			nn->next = NULL;
		}
	}
	
	void Print_Article()
	{
		article_node *temp = new article_node();
		temp = start;
		while (temp != NULL)
		{
			author_list_node *temp1 = new author_list_node();
			temp1 = temp->al;
			cout << "Title: " << temp->title << endl << "Journal: " << temp->journal << endl << "Publisher: " << temp->publisher << endl;
			cout << "Month: " << temp->month << endl << "Year: " << temp->year << endl;
			while(temp1 != NULL)
			{
				cout << "Name: " << temp1->data->name << endl;
				temp1 = temp1->next;
			}
			temp = temp->next;
			cout << endl;
		}
	}
};

int main()
{
	cout << "Hello World!" << endl;
	article_node *a_n = new article_node();
	article_list *a_l = new article_list();
	author_list_node *a_l_n = new author_list_node();
	author_data_node *a_d_n = new author_data_node();
	author_data *a_d = new author_data();
	publication_node *p_n = new publication_node();
	
	string line;
	string author;
	string title;
	string journal;
	string month;
	string year;
	string publisher;
	
	ifstream mf("DataSet.csv");
	if(mf.is_open())
	{
		int i= 0;
	    int l= 0;
	    while(getline(mf,line))
		{
			l = 0;
	        if(i == 0)
			{
			//	cout << line << '\n';
	            for(int j = 0; j < line.length(); j++)
	                if(line[j] == ',')
	                {
					//	cout << line.substr(l,j-l) << "   ";
						l = j + 1;
	                }
	              	cout << endl;
	            //	cout << line.length();
	      	}
	        else
			{
			//	cout << line << '\n';
	            int check = 0;
	            bool flag = true;
	            for(int j = 0; j < line.length(); j++)
				{
					if(line[j] == '"' && flag)
					{
					   flag = false;
					}
					else if(line[j] == '"' && !flag)
					{
					  flag=true;
					}
	            	if(line[j] == ',' && flag)
					{
	        			string x = line.substr(l, j - l);
	               		if(check == 3)
	               		{
							author = x; 
						}
						if(check == 4)
						{
							title = x;
						}
						if(check == 5)
						{
							journal = x;
						}
						if(check == 8)
						{
							month = x;
						}
						if(check == 10)
						{
							year = x;
						}
						if(check == 19)
						{
							publisher = x;
						}
						l = j + 1;
						check++;
					//	cout<<endl;
	               	}
				}
	        }
			array_list *array_l = new array_list();
        	int iterat = 1;
          	author.append(";");
          	for(int k = 0; k < author.size(); k++)
			{
        		if(author[k]== ';')
				{
	          		string nam = author.substr(iterat, (k-iterat));
	          		for(int bite = 0; bite < nam.size(); bite++)
	          			if (nam[bite] == ',')
	          			{
						  	nam.erase(nam.begin() + bite);
	          			}
						if(nam[nam.length() - 1] == '"')
	          			{
							nam.erase(nam.begin() + (nam.length() - 1));
	          			}
	          			array_l->insertEnd(nam);
	          			iterat = k + 2;
			  	}
		  	}
		 
    	    a_n = a_l->Insert_Article(title, journal, publisher, year, month);
        	for(int i = 0; i < array_l->length; i++)
			{
				a_d_n = a_d->Insert_Author(array_l->array[i]);
	        	a_l->Enter_Author_List(a_d_n, a_n);
	        	a_d->Publication_List(a_n, a_d_n);
        	}     
	   		i++;
		}
		 	a_d->Print_Author();
	    //	a_l->Print_Article();
	    
		
	    mf.close();
	}
  	else
	{
		cout << "Cant Open File." << endl;
	}
    return 0;
}
