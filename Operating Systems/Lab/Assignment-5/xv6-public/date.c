#include "types.h"
#include "user.h"
#include "date.h"

int main(int argc, char *argv[]){ 
    struct rtcdate r;
    if (date(&r)) {
        printf(2, "Date Failed\n");
        exit();
    }
    printf(1, "UTC Date:- %d-%d-%d\nTime:- %d:%d:%d\n", r.day, r.month, r.year, r.hour, r.minute, r.second);
    exit();
}