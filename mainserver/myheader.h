struct yyy
{
        char name[50];
        int roll;
        char branch[50];
        char mobno[50];
};


struct xxx
{
        struct yyy  data;
        struct xxx *ad;
};
