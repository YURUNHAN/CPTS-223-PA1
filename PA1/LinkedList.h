#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include <iostream>
#include <fstream>
#include "CmdNode.h"
using namespace std;

template <class T>
class LinkedList {
public:
	LinkedList(){
		p_head = NULL;
		m_count_Node = 0;
	};
	~LinkedList(){
		CmdNode<T>* to_delete;
		while(p_head != NULL){
			to_delete = p_head;
			p_head = p_head->getNext();
			delete to_delete;
		}
	};
	void insertAtFront(T cmdName, T cmdDescription){
		CmdNode<T>* p_newNode = new CmdNode<T>(cmdName, cmdDescription);
		if(p_head == NULL)
			p_head = p_newNode;
		else {
			p_newNode->setNext(p_head);
			p_head = p_newNode;
		}
		m_count_Node ++;
	};

	int removeNode(T cmdName){
		CmdNode<T>* to_delete;
		if(p_head == NULL)
			return 0;
		else if(p_head->getName() == cmdName) {
			to_delete = p_head;
			p_head = p_head->getNext();
			delete to_delete;
			m_count_Node --;
			return 1;
		}
		else {
			CmdNode<T>* pre_Node = p_head;
			while(pre_Node->getNext() != NULL && pre_Node->getNext()->getName() != cmdName){
				pre_Node = pre_Node->getNext();
			}
			if(pre_Node->getNext() == NULL)
				return 0;
			else {
				to_delete = pre_Node->getNext();
				pre_Node->setNext(to_delete->getNext());
				delete to_delete;
				m_count_Node --;
				return 1;
			}
		}
	};

	void resetFlag(){
		CmdNode<T>* tmp = p_head;
		while(tmp != NULL){
			tmp->setFlag(false);
			tmp = tmp->getNext();
		}
	}

	int getCount(){
		return m_count_Node;
	}

	CmdNode<T>* getAskedNode(int target_index){
		CmdNode<T>* tmp = p_head;
		int cur_index = 0;
		while(tmp != NULL){
			if(tmp->getFlag() == true) {
				tmp = tmp->getNext();
				continue;
			}
			else if(cur_index == target_index){
				return tmp;
			}
			else {
				tmp = tmp->getNext();
				cur_index += 1;
			}
		}
		return NULL;
	}

	CmdNode<T>* getUnAskedNode(CmdNode<T>* avoid_Node_1, CmdNode<T>* avoid_Node_2){
		int count_selected = m_count_Node - 1;
		if(avoid_Node_2 != NULL)
			count_selected --;
		int target_index = rand() % count_selected;

		CmdNode<T>* tmp = p_head;
		int cur_index = 0;
		while(tmp != NULL){
			if(tmp == avoid_Node_1 || tmp == avoid_Node_2) {
				tmp = tmp->getNext();
				continue;
			}
			else if(cur_index == target_index){
				return tmp;
			}
			else {
				tmp = tmp->getNext();
				cur_index += 1;
			}
		}
		return NULL;
	}

	bool existsCmd(T cmdName){
		CmdNode<T>* tmp = p_head;
		while(tmp != NULL){
			if(tmp->getName() == cmdName)
				return true;
			tmp = tmp->getNext();
		}
		return false;
	}

	void outFile(ofstream& outFile){
		CmdNode<T>* tmp = p_head;
		while(tmp != NULL){
			outFile << tmp->getName() << ",\"" << tmp->getDescription() << "\"" << endl;
			tmp = tmp->getNext();
		}
	}

private:
	CmdNode<T>* p_head;
	int m_count_Node;
};

#endif /* LINKEDLIST_H_ */
