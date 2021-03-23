
#include "stats.h"

stats::stats(PNG & im){

    // YOUR CODE HERE!!
    
   


    int ht = (int)im.height();
    int wi = (int)im.width();
    for(int x = 0; x < wi; x++) {
        vector<long> colr;
        vector<long> colr2;
        vector<long> colb;
        vector<long> colb2;
        vector<long> colg;
        vector<long> colg2;
        // cout << "Test ht = " << ht << endl;
        // cout << "Test wi = " << wi << endl;

        for(int y = 0; y < ht; y++){
            if (x==0 && y==0) {
                // cout << "Test 1 " << endl;
                colr.push_back(im.getPixel(0,0)->r);
                colr2.push_back((im.getPixel(0,0)->r)*((im.getPixel(0,0)->r)));

                colb.push_back(im.getPixel(0,0)->b);
                colb2.push_back((im.getPixel(0,0)->b)*((im.getPixel(0,0)->b)));

                colg.push_back(im.getPixel(0,0)->g);
                colg2.push_back((im.getPixel(0,0)->g)*((im.getPixel(0,0)->g)));
            } else if(y == 0) {
                // cout << "Test 2 " << endl;
                colr.push_back(im.getPixel(x,y)->r + sumRed[x-1][ht-1]);
                colr2.push_back((im.getPixel(x,y)->r)*(im.getPixel(x,y)->r) + sumsqRed[x-1][ht-1]);

                colb.push_back(im.getPixel(x,y)->b+sumBlue[x-1][ht-1]);
                colb2.push_back((im.getPixel(x,y)->b)*(im.getPixel(x,y)->b) + sumsqBlue[x-1][ht-1]);

                colg.push_back(im.getPixel(x,y)->g+sumGreen[x-1][ht-1]);
                colg2.push_back((im.getPixel(x,y)->g)*(im.getPixel(x,y)->g) + sumsqGreen[x-1][ht-1]);
            } else {
                // cout << "Test 3 " << endl;
                colr.push_back(im.getPixel(x,y)->r+colr[y-1]);
                colr2.push_back((im.getPixel(x,y)->r)*(im.getPixel(x,y)->r) + colr2[y-1]);

                colb.push_back(im.getPixel(x,y)->b+colb[y-1]);
                colb2.push_back((im.getPixel(x,y)->b)*(im.getPixel(x,y)->b) + colb2[y-1]);

                colg.push_back(im.getPixel(x,y)->g+colg[y-1]);
                colg2.push_back((im.getPixel(x,y)->g)*(im.getPixel(x,y)->g) + colg2[y-1]);
            }
        }
        
        sumRed.push_back(colr);
        sumsqRed.push_back(colr2);
        sumBlue.push_back(colb);
        sumsqBlue.push_back(colb2);
        sumGreen.push_back(colg);
        sumsqGreen.push_back(colg2);
    }

}

long stats::getSum(char channel, pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!
    long sum = 0;

	
    
    if (channel == 'r') {
        for (int x = ul.first; x < lr.first + 1 ;x++) {
            if (ul.second == 0) {
                if (x == 0) {
                    sum += (sumRed[x][lr.second]);
                } else {
                    sum += (sumRed[x][lr.second] - sumRed[x-1].back());
                }
                
            } else {
                sum += (sumRed[x][lr.second] - sumRed[x][ul.second-1]);
            }
        }
        // cout << "Test SUMRED++++++++++++++++" << sumRed[ul.first][lr.second] << endl;
    } else if(channel == 'b') {
        for (int x = ul.first; x < lr.first + 1 ;x++) {
            if (ul.second == 0) {
                if (x == 0) {
                    sum += (sumBlue[x][lr.second]);
                } else {
                    sum += (sumBlue[x][lr.second] - sumBlue[x-1].back());
                }
                
            } else {
                sum += (sumBlue[x][lr.second] - sumBlue[x][ul.second-1]);
            }
        }
    } else if(channel == 'g') {
        for (int x = ul.first; x < lr.first + 1 ;x++) {
            if (ul.second == 0) {
                if (x == 0) {
                    sum += (sumGreen[x][lr.second]);
                } else {
                    sum += (sumGreen[x][lr.second] - sumGreen[x-1].back());
                }
                
            } else {
                sum += (sumGreen[x][lr.second] - sumGreen[x][ul.second-1]);
            }
        }
    }

    return sum;
}

long stats::getSumSq(char channel, pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!
   long sum = 0;

    if (channel == 'r') {
       for (int x = ul.first; x < lr.first + 1 ;x++) {
            if (ul.second == 0) {
                if (x == 0) {
                    sum += (sumsqRed[x][lr.second]);
                } else {
                    sum += (sumsqRed[x][lr.second] - sumsqRed[x-1].back());
                }
                
            } else {
                sum += (sumsqRed[x][lr.second] - sumsqRed[x][ul.second-1]);
            }
        }
    } else if(channel == 'b') {
        for (int x = ul.first; x < lr.first + 1 ;x++) {
            if (ul.second == 0) {
                if (x == 0) {
                    sum += (sumsqBlue[x][lr.second]);
                } else {
                    sum += (sumsqBlue[x][lr.second] - sumsqBlue[x-1].back());
                }
                
            } else {
                sum += (sumsqBlue[x][lr.second] - sumsqBlue[x][ul.second-1]);
            }
        }
    } else if(channel == 'g') {
        for (int x = ul.first; x < lr.first + 1 ;x++) {
            if (ul.second == 0) {
                if (x == 0) {
                    sum += (sumsqGreen[x][lr.second]);
                } else {
                    sum += (sumsqGreen[x][lr.second] - sumsqGreen[x-1].back());
                }
                
            } else {
                sum += (sumsqGreen[x][lr.second] - sumsqGreen[x][ul.second-1]);
            }
        }
    } else {
        sum = -1;
    }
    return sum;
}

long stats::rectArea(pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!
    int w = lr.first + 1 - ul.first;
    int h = lr.second + 1 - ul.second;
    return w * h;
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
long stats::getScore(pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!
    long r = getSumSq('r',ul,lr) - (getSum('r',ul,lr)*getSum('r',ul,lr)) / rectArea(ul,lr);
    // cout << " Test Red Sum Sq = " << getSumSq('r',ul,lr) << endl;
    // cout << " Test Red Sum = " << getSum('r',ul,lr) << endl;
    // cout << endl;
    long b = getSumSq('b',ul,lr) - (getSum('b',ul,lr)*getSum('b',ul,lr)) / rectArea(ul,lr);
    long g = getSumSq('g',ul,lr) - (getSum('g',ul,lr)*getSum('g',ul,lr)) / rectArea(ul,lr);

    return r + b + g;
}
		
RGBAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){

// YOUR CODE HERE!!
long aR = getSum('r',ul,lr) / rectArea(ul,lr);
long aB = getSum('b',ul,lr) / rectArea(ul,lr);
long aG = getSum('g',ul,lr) / rectArea(ul,lr);
// cout << "Test getSum R = " << getSum('r',ul,lr) << endl;
// cout << "Test getSum R = " << getSum('r',ul,lr) << endl;
// cout << "Test getSum R = " << getSum('r',ul,lr) << endl;
RGBAPixel ret(aR, aG, aB);

return ret;
}
