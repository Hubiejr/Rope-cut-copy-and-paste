#include <iostream>
#include <string>
using namespace std;


class RopeNode{

    public:
    int weight;
    string value;
    RopeNode* left;
    RopeNode* right;

    RopeNode(int w, const string& val = ""){ // refrencing value making sure that it defaults to nothing if nothing is provided
        weight = w;
        value = val;
        left = nullptr;
        right = nullptr;
    }
};

RopeNode* buildRope(const string& n){
    int lsize = 25;

    // if the length is in the threshold create a leaf node
    if(n.length() <= lsize){
       return new RopeNode(n.length(),n); 
    }

    
    int mid = n.length() / 2; // calculates the midpoint to split the string in half

    RopeNode* leftNode = buildRope(n.substr(0, mid)); //  substrng of mid and the starting position is 0
    RopeNode* rightNode = buildRope(n.substr(mid)); 

    RopeNode* root = new RopeNode(leftNode->weight + rightNode->weight); // weight sum
    root->left = leftNode; // while addressing the children of that root node 
    root->right = rightNode;

    return root;

}

void printRope(const RopeNode& node){
    if(node.left == nullptr && node.right == nullptr){
        cout << node.value;
    }
    else{
        if(node.left != nullptr){
            printRope(*node.left);
        }
        cout << node.value;
        if(node.right != nullptr){
            printRope(*node.right);
        }
    }
}

// tracks the length of the characters
int count(const RopeNode* node) {
    if (!node) {
        return 0;
    }
    if (!node->left && !node->right) {
        return node->weight; 
    }
    return count(node->left) + count(node->right); 
}

// full text of the rope which converts into a string
string getTxt(RopeNode* node){
    if(!node){
        return "";
    }
    if(!node->left && !node->right){
        return node->value;
    }
    return getTxt(node->left) + getTxt(node->right);
}

// cut logic
RopeNode* cutRope(RopeNode* root, string& clipboard, const string& substring){
    string txt = getTxt(root);
   int pos = txt.find(substring);

   if(pos == -1){
    cout << "Substring not found\n";
    return root; 
   }

   clipboard = substring;

   txt.erase(pos,substring.length());

   delete root;
   return buildRope(txt);
}

RopeNode* pasteRope(RopeNode* root, string& clipboard, int pos){
    string txt = getTxt(root);

    if(pos > txt.length()){
        cout << "bad position";
        return root;
    }

    txt.insert(pos,clipboard);


    delete root;
    return buildRope(txt);
}

RopeNode* deleteRope(RopeNode* root, const string& substring){
    string txt = getTxt(root);

   int pos = txt.find(substring);

   if(pos == -1){
    cout << "Substring not found\n";
    return root; 
   }

   txt.erase(pos,substring.length());

   delete root;
   return buildRope(txt);
}

RopeNode* addRope(RopeNode* root, const string& substring, int pos){
    string txt = getTxt(root);

    if(pos > txt.length()){
        cout << "Invalid position " << txt.length() <<" "<<endl;
        return root;
    }
    txt.insert(pos,substring);

    delete root;
    return buildRope(txt);

}

int menu(){ // create commands inside menu
    // cout << "please type anything\n";
    string input;
    input = "Hi I am a rope";
    RopeNode* root = buildRope(input);
    // getline(cin,input);
    // RopeNode* root = buildRope(input); // call funciton with the input string


    // start of commands
    RopeNode* rope = buildRope(input); // initialize the text
    string clipboard = "";

    // main loop
    while (true){
        
        cout << "\nClipboard = " << clipboard;
        cout << "\nCurrent text:";
        printRope(*root);

        
        
        cout << "\nText length: " << count(root) << " characters\n";
        cout << "a = Add\n d = Delete\n x = Cut\n c = Copy\n p = Paste\n ";
        char command;

        cin >> command;
        cin.ignore();

        if (command == 'x'){
            cout << "Type what you would like to cut?\n";
            string cut;
            getline(cin,cut);
            root = cutRope(root,clipboard,cut);
        }
        else if (command == 'c'){
            cout << "Type something to copy:\n";
            string copy;
             getline(cin,copy);
             clipboard = copy;
             cout << "Copied to clipboard " << clipboard << endl;

        }
        else if (command == 'p'){
            cout << "Paste from clipboard\n";
            
            if(clipboard.empty()){
                cout << "Clipboard is empty\n";
                continue;
            }
            cout << "Enter the position to paste the text\n";
            int pos;
            cin >> pos;

            root = pasteRope(root,clipboard,pos);

        }
        else if(command == 'd'){
            cout << "Delete\n";

             cout << "Type something to Delete:\n";
            string del;
             getline(cin,del);
             root = deleteRope(root,del);
             cout << "Deleted " << del << endl;
        }
        else if(command == 'a'){
            cout << "Add\n";

            cout << "Type something to Add:\n";
            string add;
            getline(cin,add);

            cout << "Enter the position to insert the text\n";
            int pos;
            cin >> pos;

            cin.ignore();

            root = addRope(root,add,pos);
            cout << "Added " << add << " at position" << pos << endl;
        }

        
        else{
                cout << "Invalid command";
        }
    }
}

int main(){
    menu();
}
