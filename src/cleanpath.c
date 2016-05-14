/*
 * Copyright 2001,2016 BitMover, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "system.h"
#include "sccs.h"

int
cleanpath_main(int ac, char **av)
{
	char buf[MAXPATH];

	unless (av[1]) return (0);

	cleanPath(av[1], buf);
	printf("%s\n", buf);
	return (0);
}
