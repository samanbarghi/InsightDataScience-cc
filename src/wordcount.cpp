#include <fstream>
#include <string>
#include <iomanip>
#include "libTrie/Trie.hxx"
#include "libTrie/TrieNode.hxx"


using namespace std;
typedef ToolBox::TrieNode<unsigned> tn;

int main(int argc, char* argv[]){

    //input/output files
    string infilename,outfilename;
    infilename = argc > 1 ? argv[1] : "tweet_input/tweets.txt";
    outfilename = argc> 2 ? argv[2] : "tweet_output/ft1.txt";
    ifstream infile(infilename);
    ofstream outfile(outfilename);

    //Use a trie to keep track of tweeted words
    ToolBox::Trie<unsigned> trie(0);

   //read file line by line
   string tweet;
   while(getline(infile, tweet)){
       //pointer the beginning of each token
       int begin = 0;
       //tokenize the string and avoid unnecessary copy
       for(unsigned int i = 0; i < tweet.size(); i++ ){
           if(tweet[i] == ' ' || i == tweet.size()-1){
               //calculate what is the length of the token
               unsigned int length = (i == tweet.size()-1) ? i-begin+1 : i-begin;

               //This trie uses char* and length of the word for insertion
               //Trie is modified to increment the value if the entry already exists
               trie.addEntry(tweet.c_str()+begin, length, 1);
               //Move the beginning of the token
               begin = i+1;
           }
       }
   }
   //print content of the trie to output file
   //This is a DFS traversal
   trie.display(outfile);

   return 0;
}
