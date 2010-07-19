#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <muParser/muParser.h>

#define _USE_MATH_DEFINES
#include <cmath>

class SDroegeTest : public CppUnit::TestFixture {
public:
    CPPUNIT_TEST_SUITE (SDroegeTest);
    CPPUNIT_TEST (testSDroege_aor_0002);
    CPPUNIT_TEST_SUITE_END ();

    static double _strFunc (const char *arg0) {
      if (strcmp (arg0, "\\\"A") == 0)
        return 1;
      if (strcmp (arg0, "B") == 0)
        return 2;
      return 0;
    }

    void testSDroege_aor_0002 () {
        mu::Parser parser;
        double res;

        parser.DefineFun ("alp", &_strFunc);

        parser.SetExpr ("alp(\"\\\"A\")");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (1, res, 0.000001);

        parser.SetExpr ("alp(\"B\")");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (2, res, 0.000001);

        parser.SetExpr ("alp(\"C\")");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0, res, 0.000001);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION (SDroegeTest);

int main (int argc, char **argv)
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry ();
    runner.addTest (registry.makeTest ());
    bool wasSuccessful = runner.run ("", false);
    return (wasSuccessful != 0) ? 0 : 1;
}

