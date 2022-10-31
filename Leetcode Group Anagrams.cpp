class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>>ans; // created a ans vector to store our answer
        
        int n=strs.size();
// created a unorderes map to stor the mapping b/w the sorted word and orginal word
        
        
        unordered_map<string,vector<string>>mp;
        
        for(int i=0;i<n;i++){
            string s=strs[i];
            sort(strs[i].begin(),strs[i].end()); // sort the word
            mp[strs[i]].push_back(s); // do mapping 
        }
        for(auto it:mp){
            ans.push_back(it.second); //push it.second
        }
        
        return ans; // finally return our ans vector
    }
};
