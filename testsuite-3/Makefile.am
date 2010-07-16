TESTS = \
	test-functions\
	test-constants\
	test-userDefinitions\
	test-errors\
	test-priority\
	test-ClearUserDefinitions

noinst_PROGRAMS = $(TESTS)

TESTS_CXXFLAGS = \
	$(CPPUNIT_CFLAGS) \
	-I$(top_srcdir)
TESTS_LDADD = \
	$(CPPUNIT_LIBS) \
	$(top_builddir)/muParser/libmuparser.la

test_functions_SOURCES = functions.cxx
test_functions_CXXFLAGS = $(TESTS_CXXFLAGS)
test_functions_LDADD = $(TESTS_LDADD)

test_constants_SOURCES = constants.cxx
test_constants_CXXFLAGS = $(TESTS_CXXFLAGS)
test_constants_LDADD = $(TESTS_LDADD)

test_userDefinitions_SOURCES = userDefinitions.cxx
test_userDefinitions_CXXFLAGS = $(TESTS_CXXFLAGS)
test_userDefinitions_LDADD = $(TESTS_LDADD)

test_errors_SOURCES = errors.cxx
test_errors_CXXFLAGS = $(TESTS_CXXFLAGS)
test_errors_LDADD = $(TESTS_LDADD)

test_priority_SOURCES = priority.cxx
test_priority_CXXFLAGS = $(TESTS_CXXFLAGS)
test_priority_LDADD = $(TESTS_LDADD)

test_ClearUserDefinitions_SOURCES = ClearUserDefinitions.cxx
test_ClearUserDefinitions_CXXFLAGS = $(TESTS_CXXFLAGS)
test_ClearUserDefinitions_LDADD = $(TESTS_LDADD)

include $(top_srcdir)/tests.mak



