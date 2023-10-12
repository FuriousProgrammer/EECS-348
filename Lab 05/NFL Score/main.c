#include <stdio.h>

int main() {
    int score = 0;
    for (;;) {
        fputs("Enter 0 or 1 to STOP\n"
              "Enter the NFL score: ", stdout);
        scanf("%d", &score);
        if ( score <= 1 ) break;

        puts("\npossible combinations of scoring plays:");

        // I'm really bad at combinatorics, so using a naive approach here!
        int tmpScore = 0;
        for ( int TDp2 = 0; TDp2*8 <= score; ++TDp2 ) {
            tmpScore += TDp2*8;
            for ( int TDFG = 0; tmpScore + TDFG*7 <= score; ++TDFG ) {
                tmpScore += TDFG*7;
                for ( int TD = 0; tmpScore + TD*6 <= score; ++TD ) {
                    tmpScore += TD*6;
                    for ( int FG = (score - tmpScore)%2; tmpScore + FG*3 <= score; FG += 2 ) {
                        tmpScore += FG*3;

                        int Safe = (score - tmpScore)/2;
                        printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n", TDp2, TDFG, TD, FG, Safe);
  
                        tmpScore -= FG*3;
                    }
                    tmpScore -= TD*6;
                }
                tmpScore -= TDFG*7;
            }
            tmpScore -= TDp2*8;
      }
    }

    return 0;
}