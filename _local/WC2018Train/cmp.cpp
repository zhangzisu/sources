/**
 * Sample special-judge file
 * userout: stdin
 * input file: ./input
 * output file: ./output
 * user's code: ./usercode
 */

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <ctime>
enum SolutionResult
{
    WaitingJudge,        // Wating Judge
    Judging,             // Judging
    Skipped,             // Skipped
    Accepted,            // Accepted
    WrongAnswer,         // Wrong Answer
    TimeLimitExceeded,   // Time Limit Exceeded
    MemoryLimitExceeded, // Memory Limit Exceeded
    RuntimeError,        // Runtime Error
    CompileError,        // Compile Error
    PresentationError,   // Presentation Error
    JudgementFailed,     // Judgement Failed (Judge program error)
    SystemError,         // System Error     (Judge framwork & Judge plugin error)
    OtherError,          // Other Error
};
inline void callback(SolutionResult status, double score, const char *message)
{
    assert(score >= 0 && score <= 100);
    printf("%d\n%f\n", status, score);
    if (message)
        printf("%s\n", message);
    exit(0);
}

FILE *out = fopen("output", "r");
inline bool isWhiteChar(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n';
}
char tmp[50];
int main()
{
    int start = clock();
    for (int usr, std; usr != -1 && std != -1;)
    {
        usr = fgetc(stdin);
        std = fgetc(out);
        while (isWhiteChar(usr))
            usr = fgetc(stdin);
        while (isWhiteChar(std))
            std = fgetc(out);
        if (usr != std)
        {
            if (usr == -1)
            {
                sprintf(tmp, "Output too short");
            }
            else if (std == -1)
            {
                sprintf(tmp, "Output too long");
            }
            else
            {
                sprintf(tmp, "Read %c, expected %c", usr, std);
            }
            callback(SolutionResult::WrongAnswer, 0, tmp);
        }
    }
    int delta = clock() - start;
    sprintf(tmp, "Accepted! It took %f sec to compare", 1. * delta / CLOCKS_PER_SEC);
    callback(SolutionResult::Accepted, 100, tmp);
    return 0;
}