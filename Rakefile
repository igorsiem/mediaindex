# Rakefile for basic Dev tasks in qStub
#
# Copyright Igor Siemienowicz 2018
# Distributed under the Boost Software License, Version 1.0. (See
# accompanying file LICENSE_1_0.txt or copy at
# https://www.boost.org/LICENSE_1_0.txt)

# --- Config ---

$project_name = "mediaindex"
$project_major_version = 0
$project_minor_version = 1
$project_patch_version = 0
$project_version = "#{$project_major_version}.#{$project_minor_version}." + \
    "#{$project_patch_version}"
$project_description = "Simple media-browsing and indexing application"
$project_creator = "Igor Siemienowicz"
$project_contact = "igor@qprise.com"

# --- End Config ---

ENV['QPRJ_PROJECT_NAME'] = $project_name
ENV['QPRJ_PROJECT_MAJOR_VERSION'] = "#{$project_major_version}"
ENV['QPRJ_PROJECT_MINOR_VERSION'] = "#{$project_minor_version}"
ENV['QPRJ_PROJECT_PATCH_VERSION'] = "#{$project_patch_version}"
ENV['QPRJ_PROJECT_VERSION'] = $project_version
ENV['QPRJ_PROJECT_DESCRIPTION'] = $project_description
ENV['QPRJ_PROJECT_CREATOR'] = $project_creator
ENV['QPRJ_PROJECT_CONTACT'] = $project_contact

directory "build"

desc "clean all build artefacts"
task :clean do
    FileUtils.rm_rf "build"
end

desc "run conan to install / generate dependencies"
task :conan => "build" do
    Dir.chdir "build"
    sh "conan install ../src"
    Dir.chdir ".."
end

desc "run cmake to produce platform-specific build files"
task :cmake => :conan do
    Dir.chdir "build"

    cmake_cmd = "cmake "
    cmake_cmd += "-G \"Visual Studio 15 2017 Win64\" " \
        if Rake::Win32::windows?
    cmake_cmd += "../src"

    sh cmake_cmd

    Dir.chdir ".."
end

desc "build binaries"
task :bin => :cmake do    
    Dir.chdir "build"

    make_cmd = "make -j8"

    make_cmd =
            "msbuild /m #{$project_name}.sln " +
            "/p:Configuration=Release " +
            "/p:Platform=\"x64\" " +
            "" if Rake::Win32::windows?

    sh make_cmd

    Dir.chdir ".."
end

desc "run test suite"
task :test => :bin do
    sh "build/bin/test-#{$project_name}"
end

# Retrieve the location of Qt from conan
def get_qt_location
    cmd_str = "conan info qt/5.12.2@bincrafters/stable " +
        "--package-filter \"qt*\" " +
        "--paths --only package_folder " +
        ""

    resp_str = `#{cmd_str}`

    resp_str.lines.each do |line|
        return line.split(": ")[1].strip if line.include?("package_folder")
    end
end

# When in *nix, need to set the Qt plugin path to the conan installation
# of Qt.
if !Rake::Win32::windows?
    ENV['QT_PLUGIN_PATH'] = "#{get_qt_location}/plugins"
    # puts "set QT_PLUGIN_PATH to #{ENV['QT_PLUGIN_PATH']}"
end

desc "run the application"
task :run => :bin do

    sh "build/bin/#{$project_name}-gui " +
        "--logging-level DEB " +
        ""

end

namespace :run do

    task :help => :bin do
        sh "build/bin/#{$project_name}-gui --help"
    end
    
end

directory "build/docs"

desc "build doxygen docs"
task :docs => "build/docs" do
    sh "doxygen"
end

desc "package installer"
task :package => :bin do

    if Rake::Win32::windows?
        package_windows
    else
        package_deb
    end

end

desc "build tests, run tests and build docs"
task :all => [:bin, :test, :docs, :package]

task :default => :all

require 'pathname'

def package_deb

    FileUtils.mkpath('build/package/DEBIAN')
    open('build/package/DEBIAN/control', 'w') do |f|
        f.puts  "Package: #{$project_name}\n" \
                "Version: #{$project_version}\n" \
                "Section: custom\n" \
                "Priority: optional\n" \
                "Architecture: all\n" \
                "Essential: no\n" \
                "Installed-Size: 1024\n" \
                "Maintainer: #{$project_contact}\n" \
                "Description: #{$project_description}"
    end

    FileUtils.mkpath('build/package/usr/bin')
    FileUtils.cp('build/bin/mediaindex-gui', 'build/package/usr/bin')

    sh 'dpkg-deb -b build/package'

    FileUtils.mv( \
        'build/package.deb', \
        "build/#{$project_name}.#{$project_version}.deb")

    # TODO launcher icon

    # TODO check dependencies (use docker container)

end

def package_windows
    raise "windows packaging not supported yet"
end
