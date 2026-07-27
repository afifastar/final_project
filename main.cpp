#include "library.h"

int main()
{
    Program bsa("BSA");
    Course mth110("Mathematics", "MT110");
    Course sep101("Programming Fundamentals", "SEP101");
    Course sem105("Linear Algebra", "SEM105");
    Course mec110("Mechanics", "MEC110");

    bsa.add_course(mth110);
    bsa.add_course(sep101);
    bsa.add_course(sem105);
    bsa.add_course(mec110);

    Program bsd("BSD");

    Course btp100("Programming Fundamentals Using C", "BTP100");
    Course btl100("Computer Foundations for Developers", "BTL100");
    Course bto120("Operating Systems for Programmers - UNIX", "BTO120");

    bsd.add_course(btp100);
    bsd.add_course(btl100);
    bsd.add_course(bto120);

    Student mickey("Mickey Mouse", "13/06/2018", male, 3.1);
    Student minnie("Minnie Mouse", "21/11/2017", female, 3.9);
    Student donald("Donald Duck", "04/10/2017", male, 3.4);
    Student daisy("Daisy Duck", "08/01/2018", female, 3.6);
    Student goofy("Goofy Goof", "27/03/2018", male, 2.7);
    Student spongebob("SpongeBob SquarePants", "20/05/2011", other, 3.9);

    bsa.add_student(mickey);
    bsa.add_student(minnie);
    bsa.add_student(donald);
    bsa.add_student(daisy);
    bsa.add_student(goofy);
    bsa.add_student(spongebob);

    Student horace("Horace Horsecollar", "15/10/2017", male, 3.5);
    Student clarabelle("Clarabelle Cow", "29/01/2017", female, 3.2);
    Student scrooge("Scrooge McDuck", "12/09/2015", female, 3.9);

    bsd.add_student(horace);
    bsd.add_student(clarabelle);
    bsd.add_student(scrooge);

    donald.display();
    minnie.display();

    mickey.add_course(mth110);
    mickey.add_course(sep101);
    mickey.add_course(sem105);
    mickey.add_course(mec110);

    minnie.add_course(mth110);
    minnie.add_course(sep101);
    minnie.add_course(sem105);
    minnie.add_course(mec110);

    donald.add_course(mth110);
    donald.add_course(sep101);
    donald.add_course(sem105);

    daisy.add_course(mth110);
    daisy.add_course(sep101);
    daisy.add_course(sem105);

    goofy.add_course(mth110);
    goofy.add_course(mec110);

    mth110.display_students();
    mec110.display_students();

    horace.add_course(btp100);
    horace.add_course(btl100);

    spongebob.add_course(btp100);
    spongebob.add_course(btl100);
    spongebob.add_course(bto120);

    spongebob.display();

    btp100.display_students();

    bsa.honours_list();

    bsa.save_to_file("bsa.txt");

    Program bsa2("BSA_backup");

    bsa2.load_from_file("bsa.txt");

    bsa2.honours_list();

    return 0;
}
