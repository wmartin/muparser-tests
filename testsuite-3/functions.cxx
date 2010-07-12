#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <muParser/muParser.h>

#include <limits>
#define _USE_MATH_DEFINES
#include <cmath>

class FunctionsTest : public CppUnit::TestFixture {
public:
    CPPUNIT_TEST_SUITE (FunctionsTest);
    CPPUNIT_TEST (testSinCosTan);
    CPPUNIT_TEST (testSinhCoshTanh);
    CPPUNIT_TEST (testInverse);
    CPPUNIT_TEST (testDoubleDefinition);
    CPPUNIT_TEST_SUITE_END ();

    void testSinCosTan () {
        mu::Parser parser;
        double res;
        
        parser.DefineConst("Const_123", M_2_PI);
        
        parser.SetExpr ("sin(Const_123)^2+cos(Const_123)^2");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, res, 0.000001);
        
        parser.SetExpr ("cos(-Const_123)-cos(Const_123)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);
        
        parser.SetExpr ("sin(Const_123)-cos(_pi/2 -Const_123)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);
        
        parser.SetExpr ("sin(Const_123)/cos(Const_123)-tan(Const_123)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);
         
        parser.SetExpr ("sin(2*Const_123)-2*sin(Const_123)*cos(Const_123)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);
    }
    
    void testSinhCoshTanh () {
            mu::Parser parser;
            double res;
            
            parser.DefineConst("cONST_789", M_1_PI);
            
            parser.SetExpr ("-sinh(cONST_789)^2+cosh(cONST_789)^2");
            res = parser.Eval ();
            CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, res, 0.000001);
            
            parser.SetExpr ("cosh(-cONST_789)-cosh(cONST_789)");
            res = parser.Eval ();
            CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);
            
            parser.SetExpr ("sinh(cONST_789)/cosh(cONST_789)-tanh(cONST_789)");
            res = parser.Eval ();
            CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);
    }
    
    void testInverse () {
            mu::Parser parser;
            double res;
            
            parser.DefineConst("const", M_LN2);
            
            parser.SetExpr ("asin(sin(const))");
            res = parser.Eval ();
            CPPUNIT_ASSERT_DOUBLES_EQUAL (M_LN2, res, 0.000001);
            
            parser.SetExpr ("cos(acos(const))");
            res = parser.Eval ();
            CPPUNIT_ASSERT_DOUBLES_EQUAL (M_LN2, res, 0.000001);
            
            parser.SetExpr ("atanh(tanh(const))");
            res = parser.Eval ();
            CPPUNIT_ASSERT_DOUBLES_EQUAL (M_LN2, res, 0.000001);
        
            parser.SetExpr ("tanh(atanh(const))");
            res = parser.Eval ();
            CPPUNIT_ASSERT_DOUBLES_EQUAL (M_LN2, res, 0.000001);
            
            parser.SetExpr ("ln(exp(const))");
            res = parser.Eval ();
            CPPUNIT_ASSERT_DOUBLES_EQUAL (M_LN2, res, 0.000001);
            
            parser.SetExpr ("exp(ln(const))");
            res = parser.Eval ();
            CPPUNIT_ASSERT_DOUBLES_EQUAL (M_LN2, res, 0.000001);
        }

    void testDoubleDefinition () {
            mu::Parser parser;
            double res;
             
            parser.SetExpr ("log10(4.178093)-log(4.178093)");
            res = parser.Eval ();
            CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);
        }
};

CPPUNIT_TEST_SUITE_REGISTRATION (FunctionsTest);

int main (int argc, char **argv)
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry ();
    runner.addTest (registry.makeTest ());
    bool wasSuccessful = runner.run ("", false);
    return (wasSuccessful != 0) ? 0 : 1;
}

