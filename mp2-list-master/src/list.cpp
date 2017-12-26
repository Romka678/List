#include "list.h"
Node::Node()
{
	next = NULL;
}

Node::Node(DataType d, Node * n)
{
	data = d;
	next = n;
}

Node::Node(const Node & node2)
{
	data = node2.data;
	next = node2.next;
}

Node Node::operator=(const Node & d)
{
	data = d.data;
	next = d.next;
	return *this;
}

bool Node::operator==(const Node & node2) const
{
	int i = 0;
	if (data != node2.data)
		i++;
	if (next != node2.next)
		i++;
	if (i == 0)
		return true;
	else
		return false;

}

List::List(const List & list2)
{
	if (list2.head != NULL)
	{
		head = new Node(list2.head->data, list2.head);
		Node*tmp = head;
		Node*tmp2 = list2.head->next;
		while (tmp2 != NULL)
		{
			tmp->next = new Node(tmp2->data, tmp2->next);
			tmp = tmp->next;
			tmp2 = tmp2->next;
		}
	}
	else
	{
		head = list2.head;
	}
}

List & List::operator=(const List & list2)
{
	if(this != &list2)
	{
		Clean();
		if (list2.head != NULL)
		{
			head = new Node(list2.head->data, list2.head);
			Node*tmp = head;
			Node*tmp2 = list2.head->next;
			while (tmp2 != NULL)
			{
				tmp->next = new Node(tmp2->data, tmp2->next);
				tmp = tmp->next;
				tmp2 = tmp2->next;
			}
		}
	}
	return*this;
}

List::~List()
{
	Node*tmp = head;
	if (head != NULL)
	{
		Node*tmp2 = tmp->next;
		if (tmp != NULL)
		{
			while (tmp->next != NULL)
			{
				tmp2 = tmp->next;
				delete tmp;
				tmp = tmp2;
			}
			delete tmp;
		}
	}
}

void List::InsertToHead(const DataType & d)
{
	if (head == NULL)
	{
		head = new Node(d, NULL);
	}
	else
	{
		Node* tmp = new Node(d, head);
		this->head = tmp;
	}
}

void List::InsertToTail(const DataType & d)
{
	if (head == NULL)
	{
		head = new Node(d, NULL);
	}
	else
	{
		Node*tmp = head;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = new Node(d, NULL);
	}
}

void List::InsertAfter(Node * node, const DataType & d)
{
	if (head == NULL)
		throw"Head NULL";
	if (node != NULL)
	{
		Node*n = new Node(d, node->next);
		node->next = n;
	}
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
	if (tmp != NULL)
	{
		while ((tmp->next != NULL) && (tmp->data != d))
		{
			tmp = tmp->next;
		}
		if (tmp->data == d)
			return tmp;
		else
			return NULL;
	}
	else
		return NULL;
}

void List::Clean()
{
	Node*tmp = head;
	Node*tmp2 = head;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
		{
			tmp2 = tmp->next;
			delete tmp;
			tmp = tmp2;
		}
		delete tmp;
		head = NULL;
	}
}

int List::GetSize()
{
	Node*tmp = head;
	int k = 0;;
	if (head == NULL)
		return k;
	while (tmp != NULL)
	{
		k++;
		tmp = tmp->next;
	}
	return k;
}

void List::Inverse()
{
	if (head != NULL)
	{
		Node*tmp, *tmp2, *tmp3;
		tmp = head;
		tmp2 = NULL;
		tmp3 = head->next;
		if ((tmp != NULL) && (tmp->next != NULL))
		{
			do
			{
				tmp3 = tmp->next;
				tmp->next = tmp2;
				tmp2 = tmp;
				tmp = tmp3;
			} while (tmp != NULL);
			head = tmp2;
		}
	}
	else
		head = NULL;
}
List List::Merge(Node * node, const List & list2)
{
	if(node==NULL)
		return *this;
	if ((head == NULL) || (head==node))
	{
		List list;
		Node* tmp = list2.head;

		while (tmp != NULL)
		{
			list.InsertToTail(tmp->data);
			tmp = tmp->next;
		}
		return list;
	}
	else
	{
		List list;
		Node* tmp = head;

		while (tmp != node)
		{
			list.InsertToTail(tmp->data);
			tmp = tmp->next;
		}

		if (tmp != NULL)
		{
			list.InsertToTail(tmp->data);
			Node* tmp2 = tmp->next;
			tmp = list2.head;

			while (tmp != NULL)
			{
				list.InsertToTail(tmp->data);
				tmp = tmp->next;
			}

			tmp = tmp2;
			while (tmp != NULL)
			{
				list.InsertToTail(tmp->data);
				tmp = tmp->next;
			}
			return list;
		}
		else
		{
			Node* tmp2 = tmp;
			tmp = list2.head;

			while (tmp != NULL)
			{
				list.InsertToTail(tmp->data);
				tmp = tmp->next;
			}
			return list;
		}
	}
}
List List::Merge(const List & list2)
{
	if (head != NULL)
	{
		if (list2.head == NULL)
			return *this;
		List list(*this);
		Node* tmp = list.head;
		Node*tmp2 = list2.head;
			while (tmp->next != NULL)
			{
				tmp = tmp->next;
			}
		tmp->next = new Node(list2.head->data, NULL);
		tmp = tmp->next;
		tmp2 = tmp2->next;
			while (tmp2)
			{
				tmp->next = new Node(tmp2->data, NULL);
				tmp = tmp->next;
				tmp2 = tmp2->next;
			}
		return list;
	}
	else
	{
		List list3(list2);
		return list3;
	}
}
bool List::operator==(const List & list2) const
{
	Node*tmp = head;
	Node*tmp2 = list2.head;
	bool k = true;
	while ((tmp != NULL) && (tmp2 != NULL) && (k))
	{
		if (tmp->data != tmp2->data)
			k = false;
		tmp = tmp->next;
		tmp2 = tmp2->next;
	}
	if ((tmp != NULL) || (tmp2 != NULL))
		k = false;
	return k;
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