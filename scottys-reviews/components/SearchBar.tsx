"use client";

import { useState, useEffect, useRef } from "react";
import { Input } from "@/components/ui/input";
import { useRouter } from "next/navigation";

interface Course {
  courseid: string;
  classname: string;
  subject?: string;
  department?: string;
}

interface SearchBarProps {
  placeholder?: string;
  onCourseSelect?: (course: Course) => void;
  onSearch?: (query: string) => void;
}

export const SearchBar: React.FC<SearchBarProps> = ({
  placeholder = "Search for classes here",
  onCourseSelect,
  onSearch,
}) => {
  const [query, setQuery] = useState("");
  const [suggestions, setSuggestions] = useState<Course[]>([]);
  const [isLoading, setIsLoading] = useState(false);
  const [selectedIndex, setSelectedIndex] = useState(-1);
  const [showSuggestions, setShowSuggestions] = useState(false);
  const router = useRouter();
  const searchRef = useRef<HTMLDivElement>(null);

  useEffect(() => {
    const handleClickOutside = (event: MouseEvent) => {
      if (searchRef.current && !searchRef.current.contains(event.target as Node)) {
        setShowSuggestions(false);
      }
    };

    document.addEventListener("mousedown", handleClickOutside);
    return () => document.removeEventListener("mousedown", handleClickOutside);
  }, []);

  useEffect(() => {
    const fetchSuggestions = async () => {
      if (query.length < 2) {
        setSuggestions([]);
        setShowSuggestions(false);
        return;
      }
      setShowSuggestions(true);
      setIsLoading(true);
      try {
        const response = await fetch(`/api/courses/search?q=${encodeURIComponent(query)}`);
        if (!response || !response.ok) {
          setSuggestions([]);
          setShowSuggestions(true);
          return;
        }
        const data = await response.json();
        if (!data) {
          setSuggestions([]);
          setShowSuggestions(true);
          return;
        }
        const formattedData = data.map((course: any) => ({
          courseid: course.courseid,
          classname: course.classname,
          subject: course.subject || '',
          department: course.department || ''
        }));
        setSuggestions(formattedData);
      } catch (error) {
        // console.error("Error fetching suggestions:", error);
        setSuggestions([]);
        setShowSuggestions(true);
      } finally {
        setIsLoading(false);
        setShowSuggestions(true);
      }
    };

    fetchSuggestions();
  }, [query]);

  const handleSearch = () => {
    if (onSearch && query) {
      onSearch(query);
      setQuery(''); // 清空输入框
    }
  };

  const handleKeyDown = (e: React.KeyboardEvent) => {
    if (e.key === "ArrowDown") {
      e.preventDefault();
      setSelectedIndex((prev) => 
        prev < suggestions.length - 1 ? prev + 1 : prev
      );
    } else if (e.key === "ArrowUp") {
      e.preventDefault();
      setSelectedIndex((prev) => (prev > 0 ? prev - 1 : -1));
    } else if (e.key === "Enter" && selectedIndex >= 0) {
      e.preventDefault();
      const selectedCourse = suggestions[selectedIndex];
      handleSuggestionClick(selectedCourse);
    } else if (e.key === "Enter" && onSearch) {
      e.preventDefault();
      handleSearch();
    } else if (e.key === "Escape") {
      setShowSuggestions(false);
    }
  };

  const handleSuggestionClick = (course: Course) => {
    if (onCourseSelect) {
      onCourseSelect(course);
      setQuery("");
    } else {
      router.push(`/courses/${course.courseid}`);
    }
    setShowSuggestions(false);
    setSelectedIndex(-1);
  };

  return (
    <div className="relative w-full max-w-3xl" ref={searchRef}>
      <div className="flex items-center space-x-2" role="search">
        <Input
          className="w-full rounded-full px-6 py-3 text-md font-fredoka font-lg shadow-md focus:outline-none focus:ring-0 focus:border-transparent"
          placeholder={placeholder}
          value={query}
          onChange={(e) => {
            setQuery(e.target.value);
            setSelectedIndex(-1);
            if (e.target.value.length >= 2) {
              setShowSuggestions(true);
            }
          }}
          onKeyDown={handleKeyDown}
          onFocus={() => query.length >= 2 && setShowSuggestions(true)}
          role="textbox"
        />
        {onSearch && (
          <button
            onClick={handleSearch}
            className="px-4 py-2 bg-blue-600 text-white rounded-lg hover:bg-blue-700 focus:outline-none focus:ring-2 focus:ring-blue-500 focus:ring-offset-2"
            aria-label="Search"
          >
            Search
          </button>
        )}
      </div>
      
      {showSuggestions && (query.length >= 2 || suggestions.length > 0) && (
        <div className="absolute w-full mt-1 bg-white rounded-lg shadow-lg max-h-96 overflow-y-auto z-50">
          {isLoading ? (
            <div className="p-4 text-center text-gray-500" role="status">Loading...</div>
          ) : suggestions.length > 0 ? (
            <ul role="list" className="divide-y divide-gray-100">
              {suggestions.map((course, index) => (
                <li
                  key={course.courseid}
                  className={`px-4 py-2 cursor-pointer hover:bg-gray-100 ${
                    index === selectedIndex ? "bg-gray-100" : ""
                  }`}
                  onClick={() => handleSuggestionClick(course)}
                  role="listitem"
                  tabIndex={0}
                >
                  <div className="font-medium">
                    <span className="text-gray-600">{course.courseid}</span> - {course.classname}
                  </div>
                  <div className="text-sm text-gray-500">
                    {course.subject}
                  </div>
                </li>
              ))}
            </ul>
          ) : (
            <div className="p-4 text-center text-gray-500">No courses found</div>
          )}
        </div>
      )}
    </div>
  );
};