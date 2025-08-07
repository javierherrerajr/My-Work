import Link from 'next/link';

interface ReviewCardProps {
  review: {
    id: string;
    difficulty: number;
    quarter: string;
    professor: string;
    ta: string;
    text: string;
    user: { 
      id: string;
      username: string;
    };
    course?: {
      id: string;
      name: string;
    };
  };
}

export const ReviewCard: React.FC<{ review: ReviewCardProps["review"] }> = ({ review }) => {
  const username = review.user.username.trim();
  const userId = review.user.id;

  return (
    <div className="mt-12">
      <div className="border rounded-lg bg-white p-5 shadow-sm">
        <p className="font-black text-lg">
          {username && username !== "Anonymous" && userId ? (
            <Link
              href={`/profile/${userId}`}
              className="hover:underline hover:text-blue-500">
              {username}
            </Link>
          ) : (
            "Anonymous"
          )}
        </p>

        <div className="flex items-center text-md mb-2 text-gray-700">
          <div className="flex space-x-4">
            <span>{review.quarter}</span>
            <span>Professor: {review.professor}</span>
            <span>TA: {review.ta}</span>
          </div>
          <span className="ml-auto text-blue-700">
            Difficulty: {review.difficulty}
          </span>
        </div>

        <p className="mt-4 text-md text-black">{review.text}</p>
      </div>
    </div>
  );
};
