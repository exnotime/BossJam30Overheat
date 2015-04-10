

solution "SFMLGame"
    configurations { "Debug", "Release" }
        flags{ "Unicode", "NoPCH" } 
        libdirs { "lib" }
        includedirs { "include" }
    
        local location_path = "solution"

        if _ACTION then
	        defines { "_CRT_SECURE_NO_WARNINGS", "NOMINMAX" }

            location_path = location_path .. "/" .. _ACTION
            location ( location_path )
            location_path = location_path .. "/projects"
        end
	
	
    configuration { "Debug" }
        defines { "DEBUG" }
        flags { "Symbols" }
        
    configuration { "Release" }
        defines { "NDEBUG", "RELEASE" }
        flags { "Optimize", "FloatFast" }

		
    configuration { "Debug" }
        targetdir ( "bin/" .. "/debug" )

    configuration { "Release" } 
        targetdir ( "bin/" .. "/release" )   

		
	project "SFMLGame"
		targetname "SFMLGame" 
		debugdir ""
		location ( location_path )
		language "C++"
		kind "ConsoleApp"
		files { "src/core/**.cpp", "src/core/**.hpp", "src/core/**.h", "src/**.h", "src/**.cpp"}
		includedirs { "src/core", "include", "include/SFML", "include/glm" }
		links {}
		
		configuration {"debug"}
			links { "sfml-main-d","sfml-window-d","sfml-graphics-d","sfml-audio-d","sfml-system-d" }
		
		configuration { "Release" } 
			links { "sfml-main","sfml-window","sfml-graphics","sfml-audio","sfml-system" }	
        
    
