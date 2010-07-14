#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <muParser/muParser.h>

#include <limits>
#define _USE_MATH_DEFINES
#include <cmath>

class ConstantsTest : public CppUnit::TestFixture {
public:
    CPPUNIT_TEST_SUITE (ConstantsTest);
    CPPUNIT_TEST (testOverride);
    CPPUNIT_TEST (testNameChars);
    CPPUNIT_TEST_SUITE_END ();

    void testOverride () {
        mu::Parser parser;
        double res;
        
        parser.DefineConst("_e", 16.01);
        
        parser.SetExpr ("_e");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (16.01, res, 0.000001);
     }
    
    void testNameChars () {
            mu::Parser parser;
            double res;
            
            parser.DefineConst("_0123456789_abcdefghijklmnopqr", 2.0);
            parser.DefineConst("stuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", 1.0);
            
            parser.SetExpr ("_0123456789_abcdefghijklmnopqr");
            res = parser.Eval ();
            CPPUNIT_ASSERT_DOUBLES_EQUAL (2.0, res, 0.000001);
            
            parser.SetExpr ("stuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
            res = parser.Eval ();
            CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, res, 0.000001);
         }
};

CPPUNIT_TEST_SUITE_REGISTRATION (ConstantsTest);

int main (int argc, char **argv)
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry ();
    runner.addTest (registry.makeTest ());
    bool wasSuccessful = runner.run ("", false);
    return (wasSuccessful != 0) ? 0 : 1;
}

