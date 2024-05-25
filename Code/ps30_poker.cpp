/*
Didn't get a perfect score (90/100) : Incorrect Answer
Code modification is required
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

map<char, int> card =
{
    {'A', 0}, {'2', 1}, {'3', 2}, {'4', 3}, {'5', 4}, {'6', 5}, {'7', 6}, {'8', 7}, {'9', 8}, {'T', 9}, {'J', 10}, {'Q', 11}, {'K', 12}, { '1', 0 },
    {'S', 0}, {'D', 1}, {'H', 2}, {'C', 3}
};

bool Flush(vector<int>& suits)
{
    int max = *max_element(suits.begin(), suits.end());

    if (max >= 5)
        return true;
    else
        return false;
}

bool Triple(vector<int>& ranks)
{
    int max = *max_element(ranks.begin(), ranks.end());

    if (max == 3)
        return true;

    return false;
}

bool FourCard(vector<int>& ranks)
{
    int max = *max_element(ranks.begin(), ranks.end());

    if (max == 4)
        return true;

    return false;
}

bool OnePair(vector<int>& ranks)
{
    int max = *max_element(ranks.begin(), ranks.end());

    if (max == 2)
    {
        return true;
    }

    return false;
}

bool TwoPair(vector<int>& ranks)
{
    int max = *max_element(ranks.begin(), ranks.end());

    if (max == 2)
    {
        int count = std::count(ranks.begin(), ranks.end(), 2);

        if (ranks.front() == 2)
        {
            count--;
        }

        if (count >= 2)
            return true;

    }

    return false;
}

bool FullHouse(vector<int>& ranks)
{
    int max = *max_element(ranks.begin(), ranks.end());

    if (max == 3)
    {
        int count3 = std::count(ranks.begin(), ranks.end(), 3);
        int count2 = std::count(ranks.begin(), ranks.end(), 2);

        if (ranks.front() == 3)
            count3--;

        if (ranks.front() == 2)
            count2--;

        if (count3 == 2)
            return true;

        if (count3 == 1 && count2 >= 1)
            return true;
    }

    return false;
}

bool Straight(vector<int>& ranks)
{
    int consecutiveCount = 0;

    for (int num : ranks)
    {
        if (num != 0)
        {
            consecutiveCount++;
            if (consecutiveCount == 5)
            {
                return true;
            }
        }
        else
        {
            consecutiveCount = 0;
        }
    }

    return false;
}

bool StraightFlush(bool cards[4][14])
{
    int consecutiveCount = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 14; j++)
        {
            if (cards[i][j])
            {
                consecutiveCount++;
                if (consecutiveCount == 5)
                {
                    return true;
                }
            }
            else
            {
                consecutiveCount = 0;
            }
        }
    }
    return false;
}


int main()
{
    ifstream ifp("poker.inp");
    ofstream ofp("poker.out");

    int T;
    char c1, c2;
    ifp >> T;

    for (int t = 0; t < T; t++)
    {
        bool cards[4][14] = { false };

        vector<int> suits(4, 0);
        vector<int> ranks(14, 0);

        for (int i = 0; i < 7; i++)
        {
            ifp >> c1 >> c2;

            int suit = card[c1];
            int rank = card[c2];

            cards[suit][rank] = true;
            if (rank == 0)
                cards[suit][13] = true;
        }

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 14; j++)
            {
                if (cards[i][j])
                {
                    if (j == 0)
                        suits[i]--;
                    suits[i]++;
                    ranks[j]++;
                }
            }
        }

        if (StraightFlush(cards))
        {
            ofp << "Straight Flush" << endl;
            //cout << "Straight Flush" << endl;
        }
        else if (FourCard(ranks))
        {
            ofp << "Four Card" << endl;
            //cout << "Four Card" << endl;
        }
        else if (FullHouse(ranks))
        {
            ofp << "Full House" << endl;
            //cout << "Full House" << endl;
        }
        else if (Flush(suits))
        {
            ofp << "Flush" << endl;
            //cout << "Flush" << endl;
        }
        else if (Straight(ranks))
        {
            ofp << "Straight" << endl;
            //cout << "Straight" << endl;
        }
        else if (Triple(ranks))
        {
            ofp << "Triple" << endl;
            //cout << "Triple" << endl;
        }
        else if (TwoPair(ranks))
        {
            ofp << "Two Pair" << endl;
            //cout << "Two Pair" << endl;
        }
        else if (OnePair(ranks))
        {
            ofp << "One Pair" << endl;
            //cout << "One Pair" << endl;
        }
        else
        {
            ofp << "Top" << endl;
            //cout << "Top" << endl;
        }
    }

    ifp.close();
    ofp.close();

    return 0;
}
