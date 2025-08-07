// components/CourseCard.tsx
import Link from "next/link";
import { StarRating } from "@/components/StarRating";

interface CourseCardProps {
  course: {
    id: string;
    name: string;
    subject: string;
    department: string;
    averageRating: number;
    difficulty: number;
  };
}

export const CourseCard: React.FC<CourseCardProps> = ({ course }) => {
  return (
    <Link
      href={`/courses/${course.id}`}
      className="block bg-white shadow-md hover:shadow-lg transition rounded-lg p-4 border"
    >
      <h2 className="text-lg font-semibold">{course.name}</h2>
      <p className="text-sm text-gray-500">
        {course.department} / {course.subject}
      </p>
      <div className="mt-2">
        <span className="text-sm text-gray-600">Avg. Rating: {course.averageRating.toFixed(1)}</span>
        <StarRating rating={course.difficulty} className="mt-1" />
      </div>
    </Link>
  );
};

// Add default export for easier importing
export default CourseCard;