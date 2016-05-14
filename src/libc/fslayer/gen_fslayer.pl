#!/usr/bin/perl -w
# Copyright 2008-2010,2014-2016 BitMover, Inc
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


# create all the files for fslayer stubs
#   fslayer.h
#   fslayer_XXX_stub.c
#   fslayer.makefile

chdir "fslayer";

$bigcmt = 
"// *******************************************************\n" .
"// XXX This file is automatically generated.\n" .
"//     Edit gen_fslayer.pl instead\n" .
"//\n" .
"// DO NOT EDIT THIS FILE, YOUR CHANGES WILL BE LOST !!!!!!\n" .
"// *******************************************************\n\n";

while(<DATA>) {
    ($ret, $fcn, $args) = /^(.*)\s+fslayer_(.*)\((.*)\);/;
    next unless $ret;
    @args = split(/,\s*/, $args);
    
    push(@fcns, $fcn);
    $data{$fcn} = {
	RET => $ret,
	ARGS => join(", ", @args),   # args with types
	ANAMES => join(", ", map {$1 if /(\w+)$/} @args), #arg names
    };
}

unlink "fslayer.h";
open(H, ">fslayer.h") or die;
print H "// fslayer.h\n";
print H $bigcmt;

print H "#ifndef\tFSLAYER_NODEFINES\n";
foreach (@fcns) {
    print H "#undef\t$_\n";
    print H "#define\t$_($data{$_}{ANAMES}) fslayer_$_($data{$_}{ANAMES})\n";
}
print H "#endif\n\n";

foreach (@fcns) {
    print H "$data{$_}{RET}\tfslayer_$_($data{$_}{ARGS});\n";
}
close(H);
chmod 0444, "fslayer.h";


foreach $fcn (@fcns) {
    $fname = "fslayer_${fcn}_stub.c";
    unlink $fname;
    open(S, ">$fname") or die;
    print S "// $fname\n";
    print S $bigcmt;

    print S "#define\tFSLAYER_NODEFINES\n";
    print S "#include \"system.h\"\n";
    print S "#include \"win_remap.h\"\n";
    print S "\n";
    print S "$data{$fcn}{RET}\n";
    print S "fslayer_$fcn($data{$fcn}{ARGS})\n";
    print S "{\n";
    print S "\treturn ($fcn($data{$fcn}{ANAMES}));\n";
    print S "}\n";
    close(S);
    chmod 0444, $fname;
}

unlink "fslayer.makefile";
open(M, ">fslayer.makefile\n");
print M "# fslayer.makefile\n";
$bigcmt =~ s/\/\//#/g;
print M $bigcmt;
print M "FSLAYER_OBJS = ";
print M join(" ", map {"fslayer/fslayer_${_}_stub.o"} @fcns);
print M "\n\n";
print M "FSLAYER_HDRS = fslayer/fslayer.h\n";
print M "\n";
print M "JUNK += fslayer/fslayer.h fslayer/fslayer.makefile \\\n";
print M "\t" . join(" ", map {"fslayer/fslayer_${_}_stub.c"} @fcns) . "\n";
print M "\n";
print M "fslayer: \$(FSLAYER_OBJS)\n";
close(M);
chmod 0444, "fslayer.makefile";

__DATA__
int	fslayer_open(const char *path, int flags, mode_t mode);
int	fslayer_close(int fd);
ssize_t	fslayer_read(int fd, void *buf, size_t count);
ssize_t	fslayer_write(int fd, const void *buf, size_t count);
off_t	fslayer_lseek(int fildes, off_t offset, int whence);
int	fslayer_lstat(const char *path, struct stat *buf);
int	fslayer_linkcount(const char *path, struct stat *buf);
int	fslayer_fstat(int fd, struct stat *buf);
int	fslayer_stat(const char *path, struct stat *buf);
int	fslayer_unlink(const char *path);
int	fslayer_rename(const char *old, const char *new);
int	fslayer_chmod(const char *path, mode_t mode);
int	fslayer_link(const char *old, const char *new);
int	fslayer_symlink(const char *old, const char *new);
char**	fslayer_getdir(char *dir);
int	fslayer_access(const char *path, int mode);
int	fslayer_utime(const char *path, const struct utimbuf *buf);
int	fslayer_mkdir(const char *path, mode_t mode);
int	fslayer_rmdir(const char *path);
int	fslayer_rmIfRepo(char *path);
char*	fslayer_realBasename(const char *path, char *realname);
