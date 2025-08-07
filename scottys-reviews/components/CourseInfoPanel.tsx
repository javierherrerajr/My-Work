// components/CourseInfoPanel.tsx
import { StarRating } from "./StarRating";
import Link from "next/link";

interface Course {
  id: string;
  name: string;
  subject: string;
  department: string;
  averageRating: number;
  difficulty: number;
  passRate: number;
  prerequisites?: { id: string; name: string }[];
}

export const CourseInfoPanel: React.FC<{ course: Course }> = ({ course }) => {
  return (
    <div className="items-center">
      <h1 className="text-center text-4xl font-black font-fredoka"> {course.id}</h1>
      <h1 className="text-center text-4xl font-black font-fredoka">{course.name}</h1>

      {/* not sure if we have this info in the db
      <p className="text-sm text-gray-600 text-center">
        {course.department} / {course.subject}
      </p>
      */}

      <div className="flex gap-4 flex-wrap mt-2 text-sm text-gray-800 justify-center items-center">
        <span>Avg. Difficulty: {course.averageRating.toFixed(1)}</span>
        <StarRating rating={course.averageRating} size={18} />
      </div>
    </div>
  );
};