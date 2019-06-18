lib_LTLIBRARIES = libsfw.la

includes = $(addprefix -I$(top_srcdir)/, $(INCLUDE_PATHS))

if TARGET_WIN
os_sources = \
	src/win32/Controller.cpp \
	src/win32/ReadLoop.cpp \
	src/win32/ReadLooprunner.cpp \
	src/win32/Watcher.cpp \
	includes/win32/Controller.h \
	includes/win32/pthread.h \
	includes/win32/pthreads-win32/config.h \
	includes/win32/pthreads-win32/context.h \
	includes/win32/pthreads-win32/implement.h \
	includes/win32/pthreads-win32/need-errno.h \
	includes/win32/pthreads-win32/pthread.h \
	includes/win32/pthreads-win32/sched.h \
	includes/win32/pthreads-win32/semaphore.h \
	includes/win32/ReadLoop.h \
	includes/win32/ReadLoopRunner.h \
	includes/win32/Watcher.h
endif

if TARGET_LINUX
os_sources = \
	src/linux/InotifyEventLoop.cpp \
	src/linux/InotifyService.cpp \
	src/linux/InotifyTree.cpp \
	includes/linux/InotifyEventLoop.h \
	includes/linux/InotifyService.h \
	includes/linux/InotifyTree.h
endif

if TARGET_MAC
os_sources = \
	src/osx/FSEventsService.cpp \
	src/osx/RunLoop.cpp \
	includes/osx/FSEventsService.h \
	includes/osx/RunLoop.h
endif

common_sources = \
	../config.h \
	src/Lock.cpp \
	src/Queue.cpp \
	src/NativeInterface.cpp \
	src/SFWExport.cpp \
	includes/Lock.h \
	includes/Queue.h \
	includes/NativeInterface.h \
	includes/SingleShotSemaphore.h \
	includes/SFWExport.h

libsfw_la_SOURCES = $(common_sources) $(os_sources)

libsfw_la_CFLAGS = $(CFLAGS)
libsfw_la_CPPFLAGS = $(CPPFLAGS) $(includes)

libsfw_la_LDFLAGS = $(LDFLAGS) -no-undefined

if TARGET_MAC
libsfw_la_LDFLAGS += -shared -framework CoreServices -framework CoreFoundation
else
libsfw_la_LDFLAGS += -module
endif

$(top_builddir)/build:
	$(MKDIR_P) $@

check-local: $(top_builddir)/build
	cp .libs/*.so $< || true
	cp .libs/*.dylib $< || true
	cp .libs/*.dll $< || true
