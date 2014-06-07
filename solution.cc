// You are given a string, S, and a list of words, L, that are all of the same length. Find all starting indices of substring(s) in S that is a concatenation of each word in L exactly once and without any intervening characters.

// For example, given:
// S: "barfoothefoobarman"
// L: ["foo", "bar"]

// You should return the indices: [0,9].
// (order does not matter).

class Solution {
public:
    vector<int> findSubstring(string S, vector<string> &L) {
        vector<int> res;
        int n = L.size();
        if(!n) return res;
        int wordLen = L[0].size();
        unordered_map<string, int> strToIdx;
        vector<int> needed(n, 0);
        for(int i = 0; i < n; ++i) {
            if(!strToIdx.count(L[i]))
                strToIdx[L[i]] = i;
            ++needed[strToIdx[L[i]]];
        }
        vector<int> sIdxToStrIdx(S.size(), -1);
        for(int i = 0; i < S.size(); ++i) {
            string sub = S.substr(i,wordLen);
            if(strToIdx.count(sub)) {
                sIdxToStrIdx[i] = strToIdx[sub];
            }
        }
        
        for(int offset = 0; offset < wordLen; ++offset) {
            int start = offset;
            vector<int> found(n, 0);
            int count = 0;
            int i = start;
            while(i+wordLen <= S.size()) {
                int strIdx = sIdxToStrIdx[i];
                if(strIdx >= 0) {
                    if(++found[strIdx] <= needed[strIdx]) {
                        if(++count == n) {
                            res.push_back(start);
                        }
                    } 
                    i += wordLen;
                    if(i-start >= n*wordLen) {
                        int startStrIdx = sIdxToStrIdx[start];
                        if(--found[startStrIdx] < needed[startStrIdx]) {
                            --count;
                        }
                        start += wordLen;
                    }
                } else {
                    start = i+wordLen;
                    i = start;
                    for(int j = 0; j < n; ++j) found[j] = 0;
                    count = 0;
                }
            }
        }
        return res;
    }
};
