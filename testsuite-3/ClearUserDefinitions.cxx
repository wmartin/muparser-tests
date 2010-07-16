#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <muParser/muParser.h>

#include <limits>
#define _USE_MATH_DEFINES
#include <cmath>

class ClearDefinitionsTest : public CppUnit::TestFixture {
public:
	CPPUNIT_TEST_SUITE (ClearDefinitionsTest);
	CPPUNIT_TEST (testClearVar);
	CPPUNIT_TEST (testClearFunc);
	CPPUNIT_TEST (testClearConst);
	CPPUNIT_TEST (testClearInfixPostfix);
	CPPUNIT_TEST_SUITE_END ();

	static double _doubleSum (double arg1, double arg2) {
		return (arg1 + arg2)*2;
	}

	static double _sub (double arg1, double arg2) {
		return arg1 - arg2;
	}

	static double _infixOpr (double arg) {
		return arg*arg;
	}

	static double _postfixOpr1 (double arg) {
		return arg*1000.0;
	}

	static double _binaryFunc (double arg1, double arg2) {
		return arg1/arg2;
	}

	void testClearVar () {
		mu::Parser parser;
		double res, x;

		parser.DefineVar("x", &x);

		x = 10.0;
		parser.SetExpr ("min(100,200,300,x)");
		res = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (x, res, 0.000001);
		
		parser.ClearVar();

		try {
			parser.SetExpr("3*x");
			res = parser.Eval ();
			CPPUNIT_ASSERT (false);
		}
		catch (mu::Parser::exception_type &e) {}
	}

	void testClearFunc () {
		mu::Parser parser;
		double res;

		parser.DefineFun ("_div", &_binaryFunc);

		parser.SetExpr ("_div(1,2)");
		res = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (0.5, res, 0.000001);

		parser.ClearFun();

		try {
			parser.SetExpr("_div(1,2)");
			res = parser.Eval ();
			CPPUNIT_ASSERT_DOUBLES_EQUAL (2, res, 0.000001);
		}
		catch (mu::Parser::exception_type &e) {}
	}

	void testClearConst () {
		mu::Parser parser;
		double res;

		parser.DefineConst("_g", 9.81);

		parser.SetExpr ("sqrt(_g*_g)");
		res = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (9.81, res, 0.000001);

		parser.ClearConst();

		try {
			parser.SetExpr("abs(_g)");
			res = parser.Eval ();
			CPPUNIT_ASSERT_DOUBLES_EQUAL (2, res, 0.000001);
		}
		catch (mu::Parser::exception_type &e) {}
	}

	void testClearInfixPostfix () {
		mu::Parser parser;
		double res;

		parser.DefineInfixOprt ("~", &_infixOpr);
		parser.DefinePostfixOprt ("K", &_postfixOpr1);

		parser.SetExpr ("sqrt(~(1K))");
		res = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (1000.0, res, 0.000001);

		parser.ClearInfixOprt();

		parser.SetExpr ("1K");
		res = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (1000.0, res, 0.000001);

		try {
			parser.SetExpr("~2");
			res = parser.Eval ();
			CPPUNIT_ASSERT_DOUBLES_EQUAL (2, res, 0.000001);
		}
		catch (mu::Parser::exception_type &e) {}

		parser.ClearPostfixOprt();

		try {
			parser.SetExpr("2K");
			res = parser.Eval ();
			CPPUNIT_ASSERT_DOUBLES_EQUAL (2, res, 0.000001);
		}
		catch (mu::Parser::exception_type &e) {}

	}
};

CPPUNIT_TEST_SUITE_REGISTRATION (ClearDefinitionsTest);

int main (int argc, char **argv)
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry ();
    runner.addTest (registry.makeTest ());
    bool wasSuccessful = runner.run ("", false);
    return (wasSuccessful != 0) ? 0 : 1;
}

