
/**
 *
 * twoDtree (pa3)
 * slight modification of a Kd tree of dimension 2.
 * twoDtree.cpp
 * This file will be used for grading.
 *
 */

#include "twoDtree.h"

// Node constructor, given.
twoDtree::Node::Node(pair<int,int> ul, pair<int,int> lr, RGBAPixel a)
	:upLeft(ul),lowRight(lr),avg(a),left(NULL),right(NULL)
	{}

// twoDtree destructor, given.
twoDtree::~twoDtree(){
	clear();
}

// twoDtree copy constructor, given.
twoDtree::twoDtree(const twoDtree & other) {
	copy(other);
}


// twoDtree assignment operator, given.
twoDtree & twoDtree::operator=(const twoDtree & rhs){
	if (this != &rhs) {
		clear();
		copy(rhs);
	}
	return *this;
}

twoDtree::twoDtree(PNG & imIn){ 
// YOUR CODE HERE
	height = (int)imIn.height();
	width = (int)imIn.width();
	stats st(imIn);
	pair<int, int> ul(0,0);
	pair<int, int> lr(width-1, height-1);
	// cout << "2D Test 0" << endl;
	root = buildTree(st, ul, lr, true);
}

twoDtree::Node * twoDtree::buildTree(stats & s, pair<int,int> ul, pair<int,int> lr, bool vert) {
// YOUR CODE HERE!!
	// if (ul.first > lr.first || ul.second > lr.second) {
	// 	cin >> lr.first;
	// }
	// cout << "Test UL = " << ul.first << ", " << ul.second << endl;
	// cout << "Test LR = " << lr.first << ", " << lr.second << endl;

	twoDtree::Node* ret = new twoDtree::Node(ul,lr,s.getAvg(ul,lr));
	long minScore = -1;
    pair<int, int> newLr, newUl;
	if (ul == lr) {
		return ret;
	} else if (lr.second == ul.second) {
		vert = true;
	} else if (lr.first == ul.first) {
		vert = false;
	}
	if(vert) {
		for (int x = ul.first; x < lr.first; x++) {
			pair<int, int> p1(x, lr.second);
			pair<int, int> p2(x + 1, ul.second);
			long temp = s.getScore(ul, p1) + s.getScore(p2, lr);
			if (temp <= minScore || minScore == -1) {
				minScore = temp;
				newLr = p1;
				newUl = p2;
			}
		}
		ret->left = buildTree(s,ul,newLr,false);
   		ret->right = buildTree(s,newUl,lr,false);
	} else {
		for (int y = ul.second; y < lr.second; y++) {
			pair<int, int> p1(lr.first, y);
			pair<int, int> p2(ul.first, y + 1);
			long temp = s.getScore(ul, p1) + s.getScore(p2, lr);
			if (temp <= minScore || minScore == -1) {
				minScore = temp;
				newLr = p1;
				newUl = p2;
			}
		}
		ret->left = buildTree(s,ul,newLr,true);
   		ret->right = buildTree(s,newUl,lr,true);
	}
	
	return ret;
}

PNG twoDtree::render(){

// YOUR CODE HERE!!
	PNG ret = PNG(width, height);
	render(root, ret);
	return ret;
}

void twoDtree::render(twoDtree::Node* subRoot, PNG & img) {
	// cout << "Test Render subRoot =  " << subRoot << endl;
	// cout << "Test Render subRoot->lowRight = " << subRoot->lowRight.first << ", " << subRoot->lowRight.second << endl;
	// cout << "Test Render subRoot->upLeft = " << subRoot->upLeft.first << ", " << subRoot->upLeft.second << endl;
	if (subRoot->left == NULL && subRoot->right == NULL){
		// cout << "Test Render 1" << endl;
		for (int y = subRoot->upLeft.second; y < subRoot->lowRight.second + 1; y++){
			// cout << "Test Render 2" << endl;
			for (int x = subRoot->upLeft.first; x < subRoot->lowRight.first + 1; x++){
				// cout << "Test Render 3" << endl;
				img.getPixel(x, y)->r = subRoot->avg.r;
				img.getPixel(x, y)->g = subRoot->avg.g;
				img.getPixel(x, y)->b = subRoot->avg.b;
				img.getPixel(x, y)->a = subRoot->avg.a;
				// cout << "Test Render 4" << endl;
			}
			// cout << "Test Render 5" << endl;
		}
		// cout << "Test Render 6" << endl;
	}

	if (subRoot->left != NULL){
		render(subRoot->left, img);
	}
	if (subRoot->right != NULL){
		render(subRoot->right, img);
	}

	// cout << "Test Render 0 " << endl;
	// if (subRoot == NULL) {
	// 	return;
	// }
	// cout << "Test Render 1 = " << subRoot << endl;
    // if (subRoot->left == NULL && subRoot->right == NULL) {
	// 	cout << "Test Render 2" << endl;
	// 	// if (subRoot->upLeft.first >= 0 && subRoot->lowRight.first <= width
	// 	// &&subRoot->upLeft.second >= 0 && subRoot->lowRight.second <= height) {
	// 		for (int x = subRoot->upLeft.first; x <= subRoot->lowRight.first; x++) {
    //         	for (int y = subRoot->upLeft.second; y <= subRoot->lowRight.second; y++) {
	// 				// cout << "Test x,y = " << x << ", " << y << endl;
	// 				cout << "Test Render 3" << endl;
    //             	RGBAPixel *pixelptr = img.getPixel(x, y);
	// 				cout << "Test Render 4" << endl;
    //             	*pixelptr = subRoot->avg;
	// 				cout << "Test Render 5" << endl;
    //         	}
    //    	 	}
	// 	// } 
        
    //     return;
    // }
	// cout << "Test Render 6" << endl;
	// if (subRoot->left != NULL) {
	// 	 render(subRoot->left, img);
	// }
   
	// cout << "Test Render 7" << endl;
	// if (subRoot->right != NULL) {
	// 	render(subRoot->right, img);
	// }
    
	// cout << "Test Render 8" << endl;

	
}

int twoDtree::idealPrune(int leaves){

// YOUR CODE HERE!!

	int low=0;
	int max=20000;
	while(low<max){
		int mid=(low+max)/2;
		if(pruneSize(mid)>leaves){
			low=mid+1; 
		}
		else{
			max=mid; 
		}
	}
	return low;

}

int twoDtree::pruneSize(int tol){
	int pSize = 0;
	pruneSizeH(root, pSize, tol);
	return pSize;
}

void twoDtree::pruneSizeH(twoDtree::Node* subRoot, int& pSize, int tol) {
	if(canBePrune(subRoot->right,subRoot->avg,tol)&&canBePrune(subRoot->left,subRoot->avg,tol)){
      	pSize++;
   	}
   else{
      pruneSizeH(subRoot->left,pSize,tol);
      pruneSizeH(subRoot->right,pSize,tol);
   }

	// if (canBePrune(subRoot, subRoot->avg, tol)) {
	// 	return;
	// }
	// if (subRoot->left != NULL && subRoot->right != NULL) {
	// 	bool a = canBePrune(subRoot->left, subRoot->left->avg, tol);
	// 	bool b = canBePrune(subRoot->right, subRoot->right->avg, tol);
	// 	if (a&&b) {
	// 		// subRoot will be a leaf
	// 		pSize += 1;
	// 	} else {
	// 		if (!b) {
	// 			pruneSize(subRoot->right, pSize, tol);
	// 		} 
	// 		if (!a) {
	// 			pruneSize(subRoot->left, pSize, tol);
	// 		}
	// 	} 
	// } else if (subRoot->left != NULL) {
	// 	bool c = canBePrune(subRoot->left, subRoot->left->avg, tol);
	// 	if (c) {
	// 		pSize += 1;
	// 	} else {
	// 		pruneSize(subRoot->left, pSize, tol);
	// 	}
	// } else if (subRoot->right != NULL) {
	// 	bool d = canBePrune(subRoot->right, subRoot->right->avg, tol);
	// 	if (d) {
	// 		pSize += 1;
	// 	} else {
	// 		pruneSize(subRoot->right, pSize, tol);
	// 	}
	// } else {
	// 	pSize += 1;
	// }

}

void twoDtree::prune(int tol){
// YOUR CODE HERE!!
	if (root == NULL) {
		return;
	}
	// markAll(root, root->avg, tol);
	pruneH(root, tol);
}

twoDtree::Node* twoDtree::pruneH(twoDtree::Node* subRoot, int tol) {
	// cout << "Test prune----------" << endl;

	if (subRoot == NULL)
	{
		return NULL;
	}
	
	
	RGBAPixel avg = subRoot->avg;
	if(canBePrune(subRoot, avg, tol)){
	  clearH(subRoot->right);
	  clearH(subRoot->left);
	  }
	
	else{
	subRoot->right=pruneH(subRoot->right, tol);
	subRoot->left=pruneH(subRoot->left, tol);
	}

	return subRoot;

	// if (canBePrune(subRoot, subRoot->avg, tol)) {

	// 	subRoot = NULL;
	// 	return;
	// }
	// if (subRoot->left != NULL) {
	// 	prune(subRoot->left, tol);
	// }
	// if (subRoot->right != NULL) {
	// 	prune(subRoot->right, tol);
	// }
}


//check all leaves on that node
bool twoDtree::canBePrune(twoDtree::Node * subRoot, RGBAPixel & avg, int tol) {
	if (subRoot == NULL)
	{
		return true;
	}

	if (subRoot->left == NULL && subRoot->right == NULL)
	{
		return dist(subRoot->avg, avg, tol);
	}
	
	return (canBePrune(subRoot->left, avg, tol) && canBePrune(subRoot->right, avg,tol));
}

bool twoDtree::dist (RGBAPixel first, RGBAPixel second, int tol){
    long diffr = second.r - first.r;
    long diffg = second.g - first.g;
    long diffb = second.b - first.b;
    return ((diffr * diffr + diffg * diffg + diffb * diffb) <= tol);
}

void twoDtree::clear() {
// YOUR CODE HERE!!
	clearH(root);
	delete root;
	root = NULL;
    height = 0;
    width = 0;
}

void twoDtree::clearH(Node* &subRoot) {
	 if(subRoot == NULL) {
        return;
    }
    clearH(subRoot->left);
    clearH(subRoot->right);
    delete subRoot;
    subRoot = NULL;
}

void twoDtree::copy(const twoDtree & orig){

// YOUR CODE HERE!!
	root = copy(orig.root);
	width = orig.width;
	height = orig.height;
}

twoDtree::Node* twoDtree::copy(const twoDtree::Node* subRoot){
	if (subRoot == NULL)
        return NULL;

    // Copy this node and its children
    twoDtree::Node* newNode = new twoDtree::Node(subRoot->upLeft, subRoot->lowRight, subRoot->avg);
    newNode->left = copy(subRoot->left);
    newNode->right = copy(subRoot->right);
    return newNode;
}



