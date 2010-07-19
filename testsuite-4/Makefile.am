TESTS = \
	test-sdroege\
	test-wmartin

noinst_PROGRAMS = $(TESTS)

TESTS_CXXFLAGS = \
	$(CPPUNIT_CFLAGS) \
	-I$(top_srcdir)
TESTS_LDADD = \
	$(CPPUNIT_LIBS) \
	$(top_builddir)/muParser/libmuparser.la

test_sdroege_SOURCES = sdroege.cxx
test_sdroege_CXXFLAGS = $(TESTS_CXXFLAGS)
test_sdroege_LDADD = $(TESTS_LDADD)

test_wmartin_SOURCES = wmartin.cxx
test_wmartin_CXXFLAGS = $(TESTS_CXXFLAGS)
test_wmartin_LDADD = $(TESTS_LDADD)


include $(top_srcdir)/tests.mak



