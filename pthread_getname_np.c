/*
 * pthread_getname_np.c
 *
 * --------------------------------------------------------------------------
 *
 *      Pthreads-win32 - POSIX Threads Library for Win32
 *      Copyright(C) 1998 John E. Bossom
 *      Copyright(C) 1999,2013 Pthreads-win32 contributors
 *
 *      Homepage1: http://sourceware.org/pthreads-win32/
 *      Homepage2: http://sourceforge.net/projects/pthreads4w/
 *
 *      The current list of contributors is contained
 *      in the file CONTRIBUTORS included with the source
 *      code distribution. The list can also be seen at the
 *      following World Wide Web location:
 *      http://sources.redhat.com/pthreads-win32/contributors.html
 *
 *      This library is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU Lesser General Public
 *      License as published by the Free Software Foundation; either
 *      version 2 of the License, or (at your option) any later version.
 *
 *      This library is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *      Lesser General Public License for more details.
 *
 *      You should have received a copy of the GNU Lesser General Public
 *      License along with this library in the file COPYING.LIB;
 *      if not, write to the Free Software Foundation, Inc.,
 *      59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "pthread.h"
#include "implement.h"

int
pthread_getname_np(pthread_t thr, char *name, int len)
{
  ptw32_mcs_local_node_t threadLock;
  ptw32_thread_t * tp;
  int result;

  /* Validate the thread id. */
  result = pthread_kill (thr, 0);
  if (0 != result)
    {
      return result;
    }

  tp = (ptw32_thread_t *) thr.p;

  ptw32_mcs_lock_acquire (&tp->threadLock, &threadLock);

  //strncpy_s(name, len - 1, tp->name, len - 1);
#if defined(_MSVCRT_)
# pragma warning(suppress:4996)
  strncpy(name, tp->name, len - 1);
  tp->name[len - 1] = '\0';
#endif

  ptw32_mcs_lock_release (&threadLock);

  return 0;
}
