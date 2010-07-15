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
    	double res;

    	try {
    		// Multiplikationsoperator: 'x' statt '*'
    		parser.SetExpr("2x3");
    		res = parser.Eval ();
    		CPPUNIT_ASSERT (false);
    	}
    	catch (mu::Parser::exception_type &e) { }

    	try {
    		// String im arithm. Ausdruck
    		parser.SetExpr("value+2");
    		res = parser.Eval ();
    		CPPUNIT_ASSERT (false);
    	}
    	catch (mu::Parser::exception_type &e) { }

    	try {
    		// trig. Fkt. ohne Argument
    		parser.SetExpr("cos()");
    		res = parser.Eval ();
    		CPPUNIT_ASSERT (false);
    	}
    	catch (mu::Parser::exception_type &e) { }


    	try {
    		parser.SetExpr("sin()");
    		res = parser.Eval ();
    		CPPUNIT_ASSERT (false);
    	}
    	catch (mu::Parser::exception_type &e) { }


    	try {
    		// unvollständige trig. Fkt.  
    		parser.SetExpr("1+cos(");
    		res = parser.Eval ();
    		CPPUNIT_ASSERT (false);
    	}
    	catch (mu::Parser::exception_type &e) { }

    	try {
    		parser.SetExpr("1+sin(");
    		res = parser.Eval ();
    		CPPUNIT_ASSERT (false);
    	}
    	catch (mu::Parser::exception_type &e) { }

    	try {
    		parser.SetExpr("3*cos(2");
    		res = parser.Eval ();
    		CPPUNIT_ASSERT (false);
    	}
    	catch (mu::Parser::exception_type &e) { }

    	try {
    		parser.SetExpr("3*sin(2");
    		res = parser.Eval ();
    		CPPUNIT_ASSERT (false);
    	}
    	catch (mu::Parser::exception_type &e) { }

    	try {
    		// Dezimalbruch: ',' statt '.'
    		parser.SetExpr("2,5+1");
    		res = parser.Eval ();
    		CPPUNIT_ASSERT (false);
    	}
    	catch (mu::Parser::exception_type &e) { }

    	try {
    		// fehlende Klammer
    		parser.SetExpr("4*(2+3");
    		res = parser.Eval ();
    		CPPUNIT_ASSERT (false);
    	}
    	catch (mu::Parser::exception_type &e) { }

    	try {
    		// String als Winkel
    		parser.SetExpr("2*sin(alpha)");
    		res = parser.Eval ();
    		CPPUNIT_ASSERT (false);
    	}
    	catch (mu::Parser::exception_type &e) { }

    	try {
    		// fehlender arithm. Operator
    		parser.SetExpr("sin(2)cos(3)");
    		res = parser.Eval ();
    		CPPUNIT_ASSERT (false);
    	}
    	catch (mu::Parser::exception_type &e) { }

    	try {
    		parser.SetExpr("2sin(2)");
    		res = parser.Eval ();
    		CPPUNIT_ASSERT (false);
    	}
    	catch (mu::Parser::exception_type &e) { }

    	try {
    		// doppelter arithm. Operator
    		parser.SetExpr("sin(2)**cos(3)"); 
    		res = parser.Eval ();
    		CPPUNIT_ASSERT (false);
    	}
    	catch (mu::Parser::exception_type &e) { }

    	try {
    		parser.SetExpr("62//2");
    		res = parser.Eval ();
    		CPPUNIT_ASSERT (false);
    	}
    	catch (mu::Parser::exception_type &e) { }

    	try {
    		// leerer Ausdruck
    		parser.SetExpr("");
    		res = parser.Eval ();
    		CPPUNIT_ASSERT (false);
    	}
    	catch (mu::Parser::exception_type &e) { }

    	try {
    		// falscher Funktionsname
    		parser.SetExpr("coss(1)");
    		res = parser.Eval ();
    		CPPUNIT_ASSERT (false);
    	}
    	catch (mu::Parser::exception_type &e) { }
    } 
    
    // falsche Anzahl von Parametern    
    void testArgNumberErrors () {
        mu::Parser parser;
        double res;

        parser.DefineFun ("mult", &_binaryFunc);
 
    	try {
            parser.SetExpr ("mult(2, 2, 2)");
            res = parser.Eval ();
    		CPPUNIT_ASSERT (false);
    	}
    	catch (mu::Parser::exception_type &e) { }
        
    	try {
            parser.SetExpr ("mult(2)");
            res = parser.Eval ();
    		CPPUNIT_ASSERT (false);
    	}
    	catch (mu::Parser::exception_type &e) { }
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

