#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <muParser/muParser.h>

#define _USE_MATH_DEFINES
#include <cmath>

class PriorityTest : public CppUnit::TestFixture {
public:
    CPPUNIT_TEST_SUITE (PriorityTest);
    CPPUNIT_TEST (testArithmPriority);
    CPPUNIT_TEST (testLogicPriority);
    CPPUNIT_TEST_SUITE_END ();

    // arithmetische Operatoren
    void testArithmPriority () {
    	mu::Parser parser;
    	double res;
    	
    	parser.SetExpr("1+2*3^4");
    	res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL(163,res,0.0);
        
        parser.SetExpr("10-2^2*3/6");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL(8,res,0.0);
        
    } 
    
    // logische Operatoren
    void testLogicPriority () {
    	mu::Parser parser;
    	double res;

        parser.SetExpr ("0 and 0 or 1");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, res, 0.0);
    }    
    
};

CPPUNIT_TEST_SUITE_REGISTRATION (PriorityTest);

int main (int argc, char **argv)
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry ();
    runner.addTest (registry.makeTest ());
    bool wasSuccessful = runner.run ("", false);
    return (wasSuccessful != 0) ? 0 : 1;
}

