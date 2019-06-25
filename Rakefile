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

$build_dir = 'build'

# --- End Config ---

ENV['QPRJ_PROJECT_NAME'] = $project_name
ENV['QPRJ_PROJECT_MAJOR_VERSION'] = "#{$project_major_version}"
ENV['QPRJ_PROJECT_MINOR_VERSION'] = "#{$project_minor_version}"
ENV['QPRJ_PROJECT_PATCH_VERSION'] = "#{$project_patch_version}"
ENV['QPRJ_PROJECT_VERSION'] = $project_version
ENV['QPRJ_PROJECT_DESCRIPTION'] = $project_description
ENV['QPRJ_PROJECT_CREATOR'] = $project_creator
ENV['QPRJ_PROJECT_CONTACT'] = $project_contact

directory $build_dir

desc "clean all build artefacts"
task :clean do
    FileUtils.rm_rf $build_dir
end

desc "run conan to install / generate dependencies"
task :conan => $build_dir do
    Dir.chdir $build_dir
    sh "conan install ../src"
    Dir.chdir ".."
end

desc "run cmake to produce platform-specific build files"
task :cmake => :conan do
    Dir.chdir $build_dir

    cmake_cmd = "cmake "
    cmake_cmd += "-G \"Visual Studio 15 2017 Win64\" " \
        if Rake::Win32::windows?
    cmake_cmd += "../src"

    sh cmake_cmd

    Dir.chdir ".."
end

desc "build binaries"
task :bin => :cmake do    
    Dir.chdir $build_dir

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
    sh "#{$build_dir}/bin/test-#{$project_name}"
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

    sh "#{$build_dir}/bin/#{$project_name}-gui " +
        "--logging-level DEB " +
        ""

end

namespace :run do

    task :help => :bin do
        sh "#{$build_dir}/bin/#{$project_name}-gui --help"
    end
    
end

directory "build/docs"

desc "build doxygen docs"
task :docs => "#{$build_dir}/docs" do
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

    deb_package_dir = "#{$build_dir}/package"

    FileUtils.rm_rf deb_package_dir

    # The control file
    FileUtils.mkpath("#{deb_package_dir}/DEBIAN")
    open("#{deb_package_dir}/DEBIAN/control", 'w') do |f|
        f.puts  "Package: #{$project_name}\n" \
                "Version: #{$project_version}\n" \
                "Maintainer: #{$project_creator} <#{$project_contact}>\n" \
                "Depends: qt5-default\n" \
                "Architecture: amd64\n" \
                "Installed-Size: 1024\n" \
                "Section: custom\n" \
                "Priority: optional\n" \
                "Essential: no\n" \
                "Description: #{$project_description}"
    end

    # The application binary
    FileUtils.mkpath("#{deb_package_dir}/usr/bin")
    FileUtils.cp(
        "#{$build_dir}/bin/mediaindex-gui",
        "#{deb_package_dir}/usr/bin")

    # The application icon
    FileUtils.mkpath("#{deb_package_dir}/usr/share/icons/Humanity/apps/32")
    FileUtils.cp(
        "src/gui/resources/app-icon.svg",
        "#{deb_package_dir}/usr/share/icons/Humanity/apps/32/mediaindex.svg")

    # The desktop file entry
    FileUtils.mkpath("#{deb_package_dir}/usr/share/applications")
    open("#{deb_package_dir}/usr/share/applications/mediaindex.desktop",
            'w') do |f|
        f.puts  "[Desktop Entry]\n" \
                "Name=#{$project_name}\n" \
                "Exec=/usr/bin/mediaindex-gui\n" \
                "Type=Application\n" \
                "Categories=Utility\n" \
                "Icon=/usr/share/icons/Humanity/apps/32/mediaindex.svg"
    end

    sh 'dpkg-deb -b build/package'

    FileUtils.mv( \
        "#{$build_dir}/package.deb", \
        "#{$build_dir}/#{$project_name}.#{$project_version}.deb")

end # package_deb method

def package_windows
    # raise "windows packaging not supported yet"
    sh "makensis mediaindex.nsi"
end # package_windows method
