#ifndef CMDNODE_H_
#define CMDNODE_H_
#include <iostream>

template <class T>
class CmdNode {
public:
	CmdNode(T cmdName, T cmdDescription){
		this->cmdName = cmdName;
		this->cmdDescription = cmdDescription;
		flag_asked = false;
		p_next = NULL;
	};
	virtual ~CmdNode(){};
	CmdNode<T>* getNext(){
		return p_next;
	}
	void setNext(CmdNode<T>* p_next){
		this->p_next = p_next;
	}
	T getName(){
		return cmdName;
	}

	T getDescription(){
		return cmdDescription;
	}

	void setFlag(bool flag){
		flag_asked = flag;
	}

	bool getFlag(){
		return flag_asked;
	}

private:
	T cmdName;
	T cmdDescription;
	bool flag_asked;
	CmdNode<T>* p_next;
};

#endif /* CMDNODE_H_ */
