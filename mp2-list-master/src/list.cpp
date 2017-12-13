#include "list.h"

List::List(const List & list2)
{
	head = list2.head;
}

List & List::operator=(const List & list2)
{
	if (this != &list2)
	{
		head = list2.head;
	}
	return*this;
}

List::~List()
{
	if (head != NULL)
	{
		while (head != NULL)
		{
			Node*tmp = head->next;
			delete head;
			head = tmp;
		}
	}
}

void List::InserToHead(const DataType & d)
{
	Node*tmp;
	if (head == NULL)
	{
		head = new Node(d, NULL);
		tmp->next = NULL;
	}
	else
	{
		tmp = new Node(d, head);
		head = tmp;
	}
}

void List::InserToTail(const DataType & d)
{
	Node*tmp = head;
	if (tmp == NULL)
		head = new Node(d, NULL);
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new Node(d, NULL);
	}
}

void List::InsertAfter(Node * node, const DataType & d)
{
	Node*n = new Node(d, node->next);
	node->next = n;
}

void List::Delete(const DataType & d)
{
	Node*tmp = head, *prev = head;
	if (tmp != NULL)
	{
		while ((tmp->next != NULL) && (tmp->data != d))
		{
			prev = tmp;
			tmp = tmp->next;
		}
		if (tmp->data == d)
		{
			prev->next = tmp->next;
			if (tmp == head)
				head = head->next;
			delete tmp;
		}
	}
}

Node * List::Search(const DataType & d)
{
	Node*tmp = head;
	while (tmp != NULL)
	{
		if (tmp->data == d)
			return tmp;
		else
		{
			tmp = tmp->next;
		}
	}
	return tmp;
}

void List::Clean()
{
	Node*tmp = head;
	Node*tmp2 = head;
	while (tmp->next != NULL)
	{
		tmp2 = tmp->next->next;
		delete tmp->next;
		tmp->next = tmp2;
	}
	delete tmp;
	head = NULL;
}

int List::GetSize()
{
	Node*tmp = head;
	int k;
	while (tmp != NULL)
	{
		k++;
		tmp = tmp->next;
	}
	return k;
}

void List::Inverse()
{
	Node*tmp, *tmp2, *tmp3;
	tmp = head;
	tmp2 = NULL;
	tmp3 = tmp->next;
	if ((tmp != NULL)&&(tmp->next!=NULL))
	{
		while (tmp != NULL)
		{
			tmp3 = tmp->next;
			tmp->next=tmp2;
			tmp = tmp3;
		}
		head = tmp2;
	}
}
List List::Merge(Node * node, const List & list2)
{
	List list;
	Node*tmp = head;
	while (tmp != node)
	{
		list.InserToTail(tmp->data);
		tmp = tmp->next;
	}
	Node*tmp2 = tmp->next;
	tmp = list2.GetHead();
	while (tmp != NULL)
	{
		list.InserToTail(tmp->data);
		tmp = tmp->next;
	}
	tmp = tmp2;
	while (tmp != NULL)
	{
		list.InserToTail(tmp->data);
		tmp = tmp->next;
	}
	return list;
}
List List::Merge(const List & list2)
{
	List list;
	Node*tmp = head;
	while (tmp != NULL)
	{
		list.InserToTail(tmp->data);
		tmp = tmp->next;
	}
	tmp = list2.GetHead();
	while (tmp != NULL)
	{
		list.InserToTail(tmp->data);
		tmp = tmp->next;
	}
	return list;
}
ostream& operator<<(ostream& os, const List& l)
{
	Node*tmp = l.head;
	while (tmp != NULL)
	{
		os << tmp->data << " ";
		tmp = tmp->next;
	}
	return os;
}
