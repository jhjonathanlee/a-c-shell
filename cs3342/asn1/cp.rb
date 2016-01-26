#!/usr/bin/env ruby

require 'fileutils'

if ARGV.length != 2
  puts "Usage: ruby rb.cp src dest"
end

FileUtils.cp(ARGV[0],ARGV[1])
