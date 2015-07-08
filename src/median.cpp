#include <queue>
#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>

using namespace std;

class MaxHeapMinHeap {
private:
    priority_queue<int, vector<int>,  std::less<int> > max_heap;  // left heap
    priority_queue<int, vector<int>, std::greater<int> > min_heap;  // right heap
public:
    void insert(int num)
    {
        if(max_heap.empty() || max_heap.top() > num)
        {
            max_heap.push(num);
            if(max_heap.size() - min_heap.size() > 1)
            {
                min_heap.push(max_heap.top());
                max_heap.pop();
            }
        }
        else
        {
            min_heap.push(num);
            if(min_heap.size() > max_heap.size())
            {
                max_heap.push(min_heap.top());
                min_heap.pop();
            }
        }
    }

    double getMedian()
    {
        if(max_heap.size() > min_heap.size())
            return max_heap.top();
        else
        {
            return (max_heap.top() + min_heap.top()) / 2.0;
        }
    }
};

int main(int argc, char* argv[]){

    //input/output files
    string infilename,outfilename;
    infilename = argc > 1 ? argv[1] : "tweet_input/tweets.txt";
    outfilename = argc> 2 ? argv[2] : "tweet_output/ft2.txt";
    ifstream infile(infilename);
    ofstream outfile(outfilename);


    //Use maxmin heap to keep track of the median
    MaxHeapMinHeap maxmin;
    //This map is used to keep track of unique words
    unordered_map<std::string, bool> tmpmap;

    string tweet;
    while(getline(infile, tweet)){
        int begin = 0;
        for(unsigned int i = 0; i < tweet.size(); i++ ){
            if(tweet[i] == ' '){
                //if the word does not exist in the map, emplace insert it
                //otherwise it fails quietly. The size of this map will be
                //the number of unique words in each tweet
               tmpmap.emplace(string(tweet.c_str()+begin, i-begin), true);
                begin = i+1;


            }
        }
        //Number of unique words in the tweet
        maxmin.insert(tmpmap.size());
        //clear the map
        tmpmap.clear();
        //output the median so far
        outfile << maxmin.getMedian() << endl;
    }
    return 0;
}
