#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <muParser/muParser.h>

#define _USE_MATH_DEFINES
#include <cmath>

class ErrorsTest : public CppUnit::TestFixture {
public:
    CPPUNIT_TEST_SUITE (ErrorsTest);
    CPPUNIT_TEST (testParserErrors);
    CPPUNIT_TEST (testArgNumberErrors);    
    CPPUNIT_TEST_SUITE_END ();
    
    static double _binaryFunc (double arg1, double arg2) {
        return arg1*arg2;
    }

    // falsche Eingaben, Fehlermeldungen erwartet
    void testParserErrors () {
    	mu::Parser parser;
    	
    	// Multiplikationsoperator: 'x' statt '*'
        // CPPUNIT_ASSERT_THROW (parser.SetExpr("2x3"),mu::ParserError);
        
        // String im arithm. Ausdruck
        CPPUNIT_ASSERT_THROW (parser.SetExpr("value+2"),mu::ParserError);
        
        // trig. Fkt. ohne Argument
        CPPUNIT_ASSERT_THROW (parser.SetExpr("cos()"),mu::ParserError);
        CPPUNIT_ASSERT_THROW (parser.SetExpr("sin()"),mu::ParserError);
        
        // unvollständige trig. Fkt.  
        CPPUNIT_ASSERT_THROW (parser.SetExpr("1+cos("),mu::ParserError);
        CPPUNIT_ASSERT_THROW (parser.SetExpr("1+sin("),mu::ParserError); 
        CPPUNIT_ASSERT_THROW (parser.SetExpr("3*cos(2"),mu::ParserError);
        CPPUNIT_ASSERT_THROW (parser.SetExpr("3*sin(2"),mu::ParserError);
        
        // Dezimalbruch: ',' statt '.'
        CPPUNIT_ASSERT_THROW (parser.SetExpr("2,5+1"),mu::ParserError);

        // fehlende Klammer
        CPPUNIT_ASSERT_THROW (parser.SetExpr("4*(2+3"),mu::ParserError);
        
        // String als Winkel
        CPPUNIT_ASSERT_THROW (parser.SetExpr("2*sin(alpha)"),mu::ParserError);
        
        // fehlender arithm. Operator
        CPPUNIT_ASSERT_THROW (parser.SetExpr("sin(2)cos(3)"),mu::ParserError);
        CPPUNIT_ASSERT_THROW (parser.SetExpr("2sin(2)"),mu::ParserError);
        
        // doppelter arithm. Operator
        CPPUNIT_ASSERT_THROW (parser.SetExpr("sin(2)**cos(3)"),mu::ParserError); 
        CPPUNIT_ASSERT_THROW (parser.SetExpr("62//2"),mu::ParserError);
        CPPUNIT_ASSERT_THROW (parser.SetExpr("2--sin(2)"),mu::ParserError);
        
        // leerer Ausdruck
        CPPUNIT_ASSERT_THROW (parser.SetExpr(""),mu::ParserError);
        
        // falscher Funktionsname
        CPPUNIT_ASSERT_THROW (parser.SetExpr("coss(1)"),mu::ParserError);
    } 
    
    // falsche Anzahl von Parametern    
    void testArgNumberErrors () {
        mu::Parser parser;
        double res;

        parser.DefineFun ("mult", &_binaryFunc);
 
        parser.SetExpr ("mult(2, 2, 2)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_THROW (res, mu::ParserError);
        
        parser.SetExpr ("mult(2)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_THROW (res, mu::ParserError);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION (ErrorsTest);

int main (int argc, char **argv)
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry ();
    runner.addTest (registry.makeTest ());
    bool wasSuccessful = runner.run ("", false);
    return (wasSuccessful != 0) ? 0 : 1;
}

