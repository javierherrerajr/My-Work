// components/ClientCourseList.tsx
"use client";

import { useState, useEffect } from "react";
import { CourseCard } from "@/components/CourseCard";
import { SearchBar } from "@/components/SearchBar";

const departments = ["BCOE", "CHASS", "CNAS"];
const subjectsByDept: Record<string, string[]> = {
  BCOE: ["CS", "EE", "ME"],
  CHASS: ["PHIL", "SOC"],
  CNAS: ["MATH", "PHYS"],
};

import { Class } from "@prisma/client";

interface Course extends Class {
  subject: string;
  department: string;
  averageRating: number;
  difficulty: number;
}

export const ClientCourseList: React.FC<{ initialCourses: Class[] }> = ({
  initialCourses,
}) => {
  const [selectedDepartment, setSelectedDepartment] = useState<string | null>(null);
  const [selectedSubject, setSelectedSubject] = useState<string | null>(null);
  const [searchQuery, setSearchQuery] = useState("");
  const [courses, setCourses] = useState<Class[]>(initialCourses);
  const [isLoading, setIsLoading] = useState(false);

  useEffect(() => {
    const searchCourses = async () => {
      setIsLoading(true);
      try {
        const params = new URLSearchParams();
        if (searchQuery) params.append("q", searchQuery);
        if (selectedDepartment) params.append("department", selectedDepartment);
        if (selectedSubject) params.append("subject", selectedSubject);

        const response = await fetch(`/api/courses/search?${params.toString()}`);
        if (!response.ok) throw new Error("Search failed");
        
        const data = await response.json();
        setCourses(data);
      } catch (error) {
        console.error("Error searching courses:", error);
      } finally {
        setIsLoading(false);
      }
    };

    const debounce = setTimeout(searchCourses, 300);
    return () => clearTimeout(debounce);
  }, [searchQuery, selectedDepartment, selectedSubject]);

  return (
    <div className="flex flex-col md:flex-row gap-8">
      {/* Sidebar Filters */}
      <aside className="md:w-1/4 space-y-4">
        <div>
          <label className="block font-medium mb-1">College</label>
          <select
            className="w-full border rounded px-3 py-2"
            value={selectedDepartment || ""}
            onChange={(e) => {
              const value = e.target.value || null;
              setSelectedDepartment(value);
              setSelectedSubject(null);
            }}
          >
            <option value="">All</option>
            {departments.map((dept) => (
              <option key={dept} value={dept}>
                {dept}
              </option>
            ))}
          </select>
        </div>

        {selectedDepartment && (
          <div>
            <label className="block font-medium mb-1">Subject</label>
            <select
              className="w-full border rounded px-3 py-2"
              value={selectedSubject || ""}
              onChange={(e) => setSelectedSubject(e.target.value || null)}
            >
              <option value="">All</option>
              {(subjectsByDept[selectedDepartment] || []).map((subject) => (
                <option key={subject} value={subject}>
                  {subject}
                </option>
              ))}
            </select>
          </div>
        )}
      </aside>

      {/* Course List */}
      <section className="flex-1 space-y-6">
        <SearchBar 
          placeholder="Search courses..." 
          onSearch={setSearchQuery}
        />
        {isLoading ? (
          <div className="text-center py-4">Loading...</div>
        ) : (
          <div className="grid grid-cols-1 sm:grid-cols-2 gap-4">
            {courses.map((course) => (
              <CourseCard
                key={course.courseid}
                course={{
                  id: course.courseid,
                  name: course.classname,
                  department: course.department,
                  subject: course.subject,
                  averageRating: course.averagerating,
                  difficulty: course.difficulty,
                }}
              />
            ))}
          </div>
        )}
      </section>
    </div>
  );
};

export default ClientCourseList;