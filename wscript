#!/usr/bin/env python
# -*- coding: utf-8 -*-

def options(opt):
    opt.load('compiler_c')

def configure(conf):
    conf.load('compiler_c')
    conf.check(
        features='c cshlib',
        lib='m',
        uselib_store='M',
        msg='Checking for math library'
    )

def build(bld):
    # Build executable from proj_memalloc.c
    bld.program(
        source='src/proj_memalloc.c',
        target='mempool',
        includes='include',
        cflags=['-Wall', '-Wextra']
    )
